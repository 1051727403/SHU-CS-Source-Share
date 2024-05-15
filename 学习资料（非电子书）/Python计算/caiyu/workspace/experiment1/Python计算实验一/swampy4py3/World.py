#!/usr/bin/python

"""
This module is part of Swampy, a suite of programs available from
allendowney.com/swampy.

Copyright 2005 Allen B. Downey
Distributed under the GNU General Public License at gnu.org/licenses/gpl.html.

"""

import math
import random
import time
import threading
import sys

import tkinter
from Gui import Gui

class World(Gui):
    """Represents the environment where Animals live.
    
    A World usually includes a canvas, where animals are drawn, 
    and sometimes a control panel.
    """
    current_world = None

    def __init__(self, delay=0.5, *args, **kwds):
        Gui.__init__(self, *args, **kwds)
        self.delay = delay
        self.title('World')
        
        # keep track of the most recent world
        World.current_world = self

        # set to False when the user presses quit.
        self.exists = True    

        # list of animals that live in this world.
        self.animals = []

        # if the user closes the window, shut down cleanly
        self.protocol("WM_DELETE_WINDOW", self.quit)

    def wait_for_user(self):
        """Waits for user events and processes them."""
        try:
            self.mainloop()
        except KeyboardInterrupt:
            print('KeyboardInterrupt')

    def quit(self):
        """Shuts down the World."""
        # tell other threads that the world is gone
        self.exists = False

        # destroy closes the window
        self.destroy()
        
        # quit terminates mainloop (but since mainloop can get called
        # recursively, quitting once might not be enough!)
        Gui.quit(self)

    def sleep(self):
        """Updates the GUI and sleeps.

        Calling Tk.update from a function that might be invoked by
        an event handler is generally considered a bad idea.  For
        a discussion, see http://wiki.tcl.tk/1255

        However, in this case:
        1) It is by far the simplest option, and I want to keep this
           code readable.
        2) It is generally the last thing that happens in an event
           handler.  So any changes that happen during the update
           won't cause problems when it returns.

        Sleeping is also a potential problem, since the GUI is
        unresponsive while sleeping.  So it is probably a good idea
        to keep delay less than about 0.5 seconds.
        """
        self.update()
        time.sleep(self.delay)

    def register(self, animal):
        """Adds a new animal to the world."""
        self.animals.append(animal)

    def unregister(self, animal):
        """Removes an animal from the world."""
        self.animals.remove(animal)

    def clear(self):
        """Undraws and removes all the animals.

        And deletes anything else on the canvas.
        """
        for animal in self.animals:
            animal.undraw()
        self.animals = []
        try:
            self.canvas.delete('all')
        except AttributeError:
            print('Warning: World.clear: World must have a canvas.')

    def step(self):
        """Invoke the step method on every animal."""
        for animal in self.animals:
            animal.step()
        
    def run(self):
        """Invoke step intermittently until the user presses Quit or Stop."""
        self.running = True
        while self.exists and self.running:
            self.step()
            self.update()

    def stop(self):
        """Stops running."""
        self.running = False

    def map_animals(self, callable):
        """Apply the given callable to all animals.

        Args:
            callable: any callable object, including Gui.Callable
        """
        return list(map(callable, self.animals))

    def make_interpreter(self, gs=None):
        """Makes an interpreter for this world.
        
        Creates an attribute named inter.
        """
        self.inter = Interpreter(self, gs)
        
    def run_text(self):
        """Executes the code from the TextEntry in the control panel.

        Precondition: self must have an Interpreter and a text entry.
        """
        source = self.te_code.get(1.0, tkinter.END)
        self.inter.run_code(source, '<user-provided code>')

    def run_file(self):
        """Read the code from the filename in the entry and runs it.
        
        Precondition: self must have an Interpreter and a filename entry.
        """
        filename = self.en_file.get()
        fp = open(filename)
        source = fp.read()
        self.inter.run_code(source, filename)


class Interpreter(object):
    """Encapsulates the environment where user-provided code executes."""
    def __init__(self, world, gs=None):
        self.world = world

        # if the caller didn't provide globals, use the current env
        if gs == None:
            self.globals = globals()
        else:
            self.globals = gs
            
    def run_code_thread(self, *args):
        """Runs the given code in a new thread."""
        return MyThread(self.run_code, *args)
        
    def run_code(self, source, filename):
        """Runs the given code in the saved environment."""
        code = compile(source, filename, 'exec')
        try:
            exec(code, self.globals)
        except KeyboardInterrupt:
            self.world.quit()
        except tkinter.TclError:
            pass


class MyThread(threading.Thread):
    """Wrapper for threading.Thread.

    Improves the syntax for creating and starting threads.
    """
    def __init__(self, target, *args):
        threading.Thread.__init__(self, target=target, args=args)
        self.start()


class Animal(object):
    """Abstract class, defines the methods child classes need to provide.

    Attributes:
        world: reference to the World the animal lives in.
        x: location in Canvas coordinates
        y: location in Canvas coordinates
    """
    def __init__(self, world=None):
        self.world = world or World.current_world
        if self.world:
            self.world.register(self)
        self.x = 0
        self.y = 0

    def set_delay(self, delay):
        """Sets delay for this animal's world.

        delay is made available as an animal attribute for backward
        compatibility; ideally it should be considered an attribute
        of the world, not an animal.

        Args:
            delay: float delay in seconds
        """
        self.world.delay = delay

    delay = property(lambda self: self.world.delay, set_delay)

    def step(self):
        """Takes one step.

        Subclasses should override this method.
        """
        pass

    def draw(self):
        """Draws the animal.

        Subclasses should override this method.
        """
        pass

    def undraw(self):
        """Undraws the animal."""
        if self.world.exists and hasattr(self, 'tag'):
            self.world.canvas.delete(self.tag)

    def die(self):
        """Removes the animal from the world and undraws it."""
        self.world.unregister(self)
        self.undraw()

    def redraw(self):
        """Undraws and then redraws the animal."""
        if self.world.exists:
            self.undraw()
            self.draw()

    def polar(self, x, y, r, theta):
        """Converts polar coordinates to cartesian.
        
        Args:
            x, y: location of the origin
            r: radius
            theta: angle in degrees

        Returns:
            tuple of x, y coordinates
        """
        rad = theta * math.pi/180
        s = math.sin(rad)
        c = math.cos(rad)
        return [ x + r * c, y + r * s ]         


def wait_for_user():
    """Invokes wait_for_user on the most recent World."""
    World.current_world.wait_for_user()


if __name__ == '__main__':

    # make a generic world
    world = World()

    # create a canvas and put a text item on it
    ca = world.ca()
    ca.text([0,0], 'hello')

    # wait for the user
    wait_for_user()
