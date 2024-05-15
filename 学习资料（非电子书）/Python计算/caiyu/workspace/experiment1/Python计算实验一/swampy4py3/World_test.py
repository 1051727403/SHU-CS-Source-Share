"""This module is part of Swampy, a suite of programs available from
allendowney.com/swampy.

Copyright 2010 Allen B. Downey
Distributed under the GNU General Public License at gnu.org/licenses/gpl.html.
"""

import unittest

import World

class Tests(unittest.TestCase):

    def test_world(self):
        world = World.World()
        world.stop()
        world.quit()

    def test_animal(self):
        world = World.World()
        animal = World.Animal()
        animal.step()
        animal.draw()
        animal.undraw()
        animal.redraw()
        animal.die()

    def test_step(self):
        world = World.World()
        a1 = World.Animal()
        a1.x = 100
        a2 = World.Animal()
        a2.x = 200

        self.assertEqual(len(world.animals), 2)

        def get_x(animal): return animal.x

        res = world.map_animals(get_x)
        self.assertEqual(len(res), 2)
        self.assertEqual(res[1], 200)

        world.step()

        world.canvas = world.ca()
        world.clear()

    def test_interpreter(self):
        global x
        x = 7

        world = World.World()
        world.make_interpreter(globals())

        world.inter.run_code('x=3', 'user-provided code')
        self.assertEqual(x, 3)
        
        thread = world.inter.run_code_thread('x=5', 'user-provided code')
        thread.join()
        self.assertEqual(x, 5)

    def test_delay(self):
        world = World.World()
        animal = World.Animal()

        world.delay = 0.3
        self.assertEqual(animal.delay, 0.3)
        self.assertEqual(world.delay, 0.3)

        animal.delay = 0.4
        self.assertEqual(animal.delay, 0.4)
        self.assertEqual(world.delay, 0.4)

        
        

if __name__ == '__main__':
    unittest.main()
