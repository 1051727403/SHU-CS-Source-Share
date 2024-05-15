#!/usr/bin/python

"""This module is part of Swampy, a suite of programs available from
allendowney.com/swampy.

Copyright 2010 Allen B. Downey
Distributed under the GNU General Public License at gnu.org/licenses/gpl.html.


UML diagrams for Python

Lumpy generates UML diagrams (currently object and class diagrams)
from a running Python program. It is similar to a graphical debugger
in the sense that it generates a visualization of the state of a
running program, but it is different from a debugger in the sense that
it tries to generate high-level visualizations that are compliant (at
least in spirit) with standard UML.

There are three target audiences for this module: teachers, students
and software engineers. Teachers can use Lumpy to generate figures
that demonstrate a model of the execution of a Python
program. Students can use Lumpy to explore the behavior of the Python
interpreter. Software engineers can use Lumpy to extract the structure
of existing programs by diagramming the relationships among the
classes, including classes defined in libraries and the Python
interpreter.

"""

import inspect
import sys

import tkinter
from tkinter import N, S, E, W, SW, HORIZONTAL, ALL, LAST

from Gui import Gui, GuiCanvas, Point, BBox, underride, ScaleTransform

# get the version of Python
VERSION = sys.version.split()[0].split('.')
MAJOR = int(VERSION[0])

if MAJOR < 2:
    print('You must have at least Python version 2.0 to run Lumpy.')
    sys.exit()

MINOR = int(VERSION[1])
if MAJOR == 2 and MINOR < 4:
    # TODO: provide a substitute implementation of set
    pass
        
if MAJOR == 2:
    TKINTER_MODULE = Tkinter
else:
    TKINTER_MODULE = tkinter

# most text uses the font specified below; some labels
# in object diagrams use smallfont.  Lumpy uses the size
# of the fonts to define a length unit, so
# changing the font sizes will cause the whole diagram to
# scale up or down.
FONT = ("Helvetica", 10)
SMALLFONT = ("Helvetica", 9)


class DiagCanvas(GuiCanvas):
    """Canvas for displaying Diagrams."""
    
    def box(self, box, padx=0.4, pady=0.2, **options):
        """Draws a rectangle with the given bounding box.

        Args:
            box: BBox object or list of coordinate pairs.
            padx, pady: padding
        """

        # underride sets default values only if the called hasn't
        underride(options, outline='black')
        box.left -= padx
        box.top -= pady
        box.right += padx
        box.bottom += pady
        item = self.rectangle(box, **options)
        return item

    def arrow(self, start, end, **options):
        """Draws an arrow.

        Args:
            start: Point or coordinate pair.
            end: Point or coordinate pair.
        """
        return self.line([start, end], **options)

    def offset_text(self, pos, text, dx=0, dy=0, **options):
        """Draws the given text at the given position.

        Args:
            pos: Point or coordinate pair
            text: string
            dx, dy: offset
        """
        underride(options, fill='black', font=FONT, anchor=W)
        x, y = pos
        x += dx
        y += dy
        return self.text([x, y], text, **options)
        
    def dot(self, pos, r=0.2, **options):
        """Draws a dot at the given position with radius r."""
        underride(options, fill='white', outline='orange')
        return self.circle(pos, r, **options)
        
    def measure(self, t, **options):
        """Finds the bounding box of the list of words.

        Draws the text, measures them, and then deletes them.
        """
        pos = Point([0, 0])
        tags = 'temp'
        for s in t:
            self.offset_text(pos, s, tags=tags, **options)
            pos.y += 1
        bbox = self.bbox(tags)
        self.delete(tags)
        return bbox
    

class MakeTag(object):
    """Encapsulates a unique Tag generator."""

    nextid = 0

    @classmethod
    def make_tag(cls, prefix='Tag'):
        """Return a tuple with a single element: a tag string.

        Uses the given prefix and a unique id as a suffix.

        prefix: string

        returns: string
        """
        cls.nextid += 1
        tag = '%s%d' % (prefix, cls.nextid)
        return tag,


class Thing(object):
    """Parent class for objects that have a graphical representation. 

    Each Thing object corresponds to an item
    or set of items in a diagram.  A Thing can only be drawn in
    one Diagram at a time.
    """
    things_created = 0
    things_drawn = 0

    def __new__(cls, *args, **kwds):
        """Override __new__ so we can count the number of Things."""
        Thing.things_created += 1
        return object.__new__(cls)
    
    def get_bbox(self):
        """Returns the bounding box of this object if it is drawn."""
        return self.canvas.bbox(self.tags)
    
    def set_offset(self, pos):
        """Sets the offset attribute.

        The offset attribute keeps track of the offset between
        the bounding box of the Thing and its nominal position, so
        that if the Thing is moved later, we can compute its new
        nominal position.
        """
        self.offset = self.get_bbox().offset(pos)

    def pos(self):
        """Computes the nominal position of a Thing.

        Gets the current bounding box and adds the offset.
        """
        return self.get_bbox().pos(self.offset)

    def isdrawn(self):
        """Return True if the object has been drawn."""
        return hasattr(self, 'drawn')

    def draw(self, diag, pos, flip, tags=tuple()):
        """Draws this Thing at the given position.

        Most child classes use this method as a template and
        override drawme() to provide type-specific behavior.

        draw() and drawme() are not allowed to modify pos.

        Args:
           diag: which diagram to draw on
           pos: Point or coordinate pair
           flip: int (1 means draw left to right; flip=-1 means right to left)
           tags: additional tags to apply

        Returns:
           list of Thing objects
        """
        if self.isdrawn():
            return []

        self.drawn = True
        self.diag = diag
        self.canvas = diag.canvas

        # keep track of how many things have been drawn.
        # Simple values can get drawn more than once, so the
        # total number of things drawn can be greater than
        # the number of things.
        Thing.things_drawn += 1
        if Thing.things_drawn % 100 == 0:
            print(Thing.things_drawn)

            # uncomment this to see things as they are drawn
            #self.diag.lumpy.update()

        # each thing has a list of tags: its own tag plus
        # the tag of each thing it belongs to.  This convention
        # makes it possible to move entire structures with one
        # move command.
        self.tags = MakeTag.make_tag(self.__class__.__name__)
        tags += self.tags

        # invoke drawme in the child class
        drawn = self.drawme(diag, pos, flip, tags)
        if drawn == None:
            drawn = [self]
            
        self.set_offset(pos)
        return drawn

    def drawme(self, diag, pos, flip, tags):
        raise ValueError('Unimplemented method.')

    def bind(self, tags=None):
        """Create bindings for the items with the given tags."""
        tags = tags or self.tags
        items = self.canvas.find_withtag(tags)
        for item in items:
            self.canvas.tag_bind(item, "<Button-1>", self.down)

    def down(self, event):
        """Save state for the beginning of a drag and drop.

        Callback invoked when the user clicks on an item.
        """
        self.dragx = event.x
        self.dragy = event.y
        self.canvas.bind("<B1-Motion>", self.motion)
        self.canvas.bind("<ButtonRelease-1>", self.up)
        return True

    def motion(self, event):
        """Move the Thing during a drag.

        Callback invoked when the user drags an item"""
        dx = event.x - self.dragx
        dy = event.y - self.dragy

        self.dragx = event.x
        self.dragy = event.y

        self.canvas.move(self.tags, dx, dy)
        self.diag.update_arrows()
  
    def up(self, event):
        """Release the object being dragged.

        Callback invoked when the user releases the button.
        """
        event.widget.unbind ("<B1-Motion>")
        event.widget.unbind ("<ButtonRelease-1>")
        self.diag.update_arrows()


class Dot(Thing):
    """Represents a dot in a diagram."""
    def drawme(self, diag, pos, flip, tags=tuple()):
        """Draws the Thing."""
        self.canvas.dot(pos, tags=tags)


class Simple(Thing):
    """Represents a simple value like a number or a string."""

    def __init__(self, lumpy, val):
        lumpy.register(self, val)
        self.val = val

    def drawme(self, diag, pos, flip, tags=tuple()):
        """Draws the Thing."""
        p = pos.copy()
        p.x += 0.1 * flip        
        anchor = {1:W, -1:E}

        # put quotes around strings; for everything else, use
        # the standard str representation
        val = self.val
        maxlen = 30
        if isinstance(val, str):
            val = val.strip('\n')
            label = "'%s'" % val[0:maxlen]
        else:
            label = str(val)
        
        self.canvas.offset_text(p, label, tags=tags, anchor=anchor[flip])
        self.bind()


class Index(Simple):
    """Represents an index in a Sequence.

    An Index object does not register with lumpy, so that even
    in pedantic mode, it is always drawn, and it is never the
    target of a reference (since it is not really a value at
    run-time).
    """
    def __init__(self, _, val):
        self.val = val

    def drawme(self, diag, pos, flip, tags=tuple()):
        """Draws the Thing."""
        p = pos.copy()
        p.x += 0.1 * flip        
        anchor = {1:W, -1:E}

        label = str(self.val)
        
        self.canvas.offset_text(p, label, tags=tags, anchor=anchor[flip])
        self.bind()


class Mapping(Thing):
    """Represents a mapping type (usually a dictionary).

    Sequence and Instance inherit from Mapping.
    """
    def __init__(self, lumpy, val):
        lumpy.register(self, val)
        self.bindings = make_kvps(lumpy, list(val.items()))
        self.boxoptions = dict(outline='purple')
        self.label = type(val).__name__

    def get_bbox(self):
        """Gets the bounding box for this Mapping.

        The bbox of a Mapping is the bbox of its box item.
        This is different from other Things.
        """
        return self.canvas.bbox(self.boxitem)

    def drawme(self, diag, pos, flip, tags=tuple()):
        """Draws the Thing."""
        p = pos.copy()

        # intag is attached to items that should be considered
        # inside the box
        intag = self.tags[0] + 'inside'

        # draw the bindings
        for binding in self.bindings:
            # check whether the key was already drawn
            drawn = binding.key.isdrawn()

            # draw the binding
            binding.draw(diag, p, flip, tags=tags)

            # apply intag to the dots 
            self.canvas.addtag_withtag(intag, binding.dot.tags)
            if drawn:
                # if the key was already drawn, then the binding
                # contains two dots, so we should add intag to the
                # second one.
                if binding.dot2:
                    self.canvas.addtag_withtag(intag, binding.dot2.tags)
            else:
                # if the key wasn't drawn yet, it should be
                # considered inside this mapping
                self.canvas.addtag_withtag(intag, binding.key.tags)

            # move down to the position for the next binding
            p.y = binding.get_bbox().bottom + 1.8

        if len(self.bindings):
            # if there are any bindings, draw a box around them
            bbox = self.canvas.bbox(intag)
            item = self.canvas.box(bbox, tags=tags, **self.boxoptions)
        else:
            # otherwise just draw a box
            bbox = BBox([p.copy(), p.copy()])
            item = self.canvas.box(bbox, padx=0.4, pady=0.4, tags=tags,
                              **self.boxoptions)

        # make the box clickable
        self.bind(item)
        self.boxitem = item

        # put the label above the box
        if self.label:
            p = bbox.upperleft()
            item = self.canvas.offset_text(p, self.label, anchor=SW,
                              font=SMALLFONT, tags=tags)
            # make the label clickable
            self.bind(item)

        # if the whole mapping is not in the right position, shift it.
        if flip == 1:
            dx = pos.x - self.get_bbox().left
        else:
            dx = pos.x - self.get_bbox().right

        self.canvas.move(self.tags, dx, 0, transform=True)

    def scan_bindings(self, cls):
        """Looks for references to other types.

        Invokes add_hasa on cls.

        Args:
            cls: is the Class of the object that contains this mapping.
        """
        for binding in self.bindings:
            for val in binding.vals:
                self.scan_val(cls, val)

    def scan_val(self, cls, val):
        """Looks for references to other types.

        If we find a reference to an object type, make a note
        of the HAS-A relationship.  If we find a reference to a
        container type, scan it for references.

        Args:
            cls: is the Class of the object that contains this mapping.
        """        
        if isinstance(val, Instance) and val.cls is not None:
            cls.add_hasa(val.cls)
        elif isinstance(val, Sequence):
            val.scan_bindings(cls)
        elif isinstance(val, Mapping):
            val.scan_bindings(cls)
        

class Sequence(Mapping):
    """Represents a sequence type (mostly lists and tuples)."""

    def __init__(self, lumpy, val):
        lumpy.register(self, val)
        self.bindings = make_bindings(lumpy, enumerate(val))

        self.label = type(val).__name__

        # color code lists, tuples, and other sequences
        if isinstance(val, list):
            self.boxoptions = dict(outline='green1')
        elif isinstance(val, tuple):
            self.boxoptions = dict(outline='green4')
        else:
            self.boxoptions = dict(outline='green2')


class Instance(Mapping):
    """Represents an object (usually).

    Anything with a __dict__ is treated as an Instance.
    """
    def __init__(self, lumpy, val):
        lumpy.register(self, val)

        # if this object has a class, make a Thing to
        # represent the class, too
        if hasclass(val):
            class_or_type = val.__class__
            self.cls = make_thing(lumpy, class_or_type)
        else:
            class_or_type = type(val)
            self.cls = None
            
        self.label = class_or_type.__name__

        if class_or_type in lumpy.instance_vars:
            # if the class is in the list, only display only the
            # unrestricted instance variables
            ks = lumpy.instance_vars[class_or_type]
            it = [(k, getattr(val, k)) for k in ks]
            seq = make_bindings(lumpy, it)
        else:
            # otherwise, display all of the instance variables
            if hasdict(val):
                it = list(val.__dict__.items())
            elif hasslots(val):
                it = [(k, getattr(val, k)) for k in val.__slots__]
            else:
                t = [k for k, v in type(val).__dict__.items()
                     if str(v).find('attribute') == 1]
                it = [(k, getattr(val, k)) for k in t]
            
            seq = make_bindings(lumpy, it)

            # and if the object extends list, tuple or dict,
            # append the items
            if isinstance(val, (list, tuple)):
                seq += make_bindings(lumpy, enumerate(val))

            if isinstance(val, dict):
                seq += make_bindings(lumpy, list(val.items()))

        # if this instance has a name attribute, show it
        attr = '__name__'
        if hasname(val):
            seq += make_bindings(lumpy, [[attr, val.__name__]])

        self.bindings = seq
        self.boxoptions = dict(outline='red')

    def scan_bindings(self, cls):
        """Look for references to other types.

        Invokes add_ivar and add_hasa on cls.
        Records the names of the instance variables.

        Args:
            cls: is the Class of the object that contains this mapping.
        """
        for binding in self.bindings:
            cls.add_ivar(binding.key.val)
            for val in binding.vals:
                self.scan_val(cls, val)


class Frame(Mapping):
    """Represents a frame."""
    def __init__(self, lumpy, frame):
        it = list(frame.locals.items())
        self.bindings = make_bindings(lumpy, it)
        self.label = frame.func
        self.boxoptions = dict(outline='blue')
    

class Class(Instance):
    """Represents a Class.

    Inherits from Instance, which controls how a Class appears in an
    object diagram, and contains a ClassDiagramClass, which
    controls how the Class appears in a class diagram.
    """
    def __init__(self, lumpy, classobj):
        Instance.__init__(self, lumpy, classobj)
        self.cdc = ClassDiagramClass(lumpy, classobj)
        self.cdc.cls = self
        
        lumpy.classes.append(self)
        
        self.classobj = classobj
        self.module = classobj.__module__
        self.bases = classobj.__bases__

        # childs is the list of classes that inherit directly
        # from this one; parents is the list of base classes
        # for this one
        self.childs = []

        # refers is a dictionary that records, for each other
        # class, the total number of references we have found from
        # this class to that
        self.refers = {}

        # make a list of Things to represent the
        # parent classes
        if lumpy.is_opaque(classobj):
            self.parents = []
        else:
            self.parents = [make_thing(lumpy, base) for base in self.bases]

        # add self to the parents' lists of children
        for parent in self.parents:
            parent.add_child(self)

        # height and depth are used to lay out the tree
        self.height = None
        self.depth = None
        
    def add_child(self, child):
        """Adds a child.

        When a subclass is created, it notifies its parent
        classes, who update their list of children."""
        self.childs.append(child)

    def add_hasa(self, child, n=1):
        """Increment the reference count from this class to a child."""
        self.refers[child] = self.refers.get(child, 0) + n

    def add_ivar(self, var):
        """Adds to the set of instance variables for this class."""
        self.cdc.ivars.add(var)

    def set_height(self):
        """Computes the maximum height between this class and a leaf class.
        
        (A leaf class has no children)
        Sets the height attribute.
        """
        if self.height != None:
            return
        if not self.childs:
            self.height = 0
            return
        for child in self.childs:
            child.set_height()
            
        heights = [child.height for child in self.childs]
        self.height = max(heights) + 1

    def set_depth(self):
        """Compute the maximum depth between this class and a root class.

        (A root class has no parent)
        Sets the depth attribute.
        """
        if self.depth != None:
            return
        if not self.parents:
            self.depth = 0
            return
        for parent in self.parents:
            parent.set_depth()
            
        depths = [parent.depth for parent in self.parents]
        self.depth = max(depths) + 1


class ClassDiagramClass(Thing):
    """Represents a class as it appears in a class diagram."""
    def __init__(self, lumpy, classobj):
        self.lumpy = lumpy
        self.classobj = classobj

        # self.methods is the list of methods defined in this class.
        # self.cvars is the list of class variables.
        # self.ivars is a set of instance variables.
        
        self.methods = []
        self.cvars = []
        self.ivars = set()

        # if this is a restricted (or opaque) class, then
        # vars contains the list of instance variables that
        # will be shown; otherwise it is None.
        try:
            variables = lumpy.instance_vars[classobj]
        except KeyError:
            variables = None

        # we can get methods and class variables now, but we
        # have to wait until the Lumpy representation of the stack
        # is complete before we can go looking for instance vars.
        for key, val in list(classobj.__dict__.items()):
            if variables is not None and key not in variables:
                continue
            
            if iscallable(val):
                self.methods.append(val)
            else:
                self.cvars.append(key)

        key = lambda x: x.__class__.__name__ + "."  + x.__name__
        self.methods.sort(key=key)
        self.cvars.sort()

        self.boxoptions = dict(outline='blue')
        self.lineoptions = dict(fill='blue')


    def drawme(self, diag, pos, flip, tags=tuple()):
        """Draws the Thing."""
        p = pos.copy()

        # draw the name of the class
        name = self.classobj.__name__
        item = self.canvas.offset_text(p, name, tags=tags)
        p.y += 0.8

        # in order to draw lines between segments, we have
        # to store the locations and draw the lines, later,
        # when we know the location of the box
        lines = []

        # draw a line between the name and the methods
        if self.methods:
            lines.append(p.y)
            p.y += 1

        # draw the methods
        for f in self.methods:
            item = self.canvas.offset_text(p, f.__name__, tags=tags)
            p.y += 1

        # draw the class variables
        cvars = [var for var in self.cvars if not var.startswith('__')]
        if cvars:
            lines.append(p.y)
            p.y += 1

        for varname in cvars:
            item = self.canvas.offset_text(p, varname, tags=tags)
            p.y += 1

        # if this is a restricted (or opaque) class, remove
        # unwanted instance vars from self.ivars
        try:
            variables = self.lumpy.instance_vars[self.classobj]
            self.ivars.intersection_update(variables)
        except KeyError:
            pass
            
        # draw the instance variables
        ivars = list(self.ivars)
        ivars.sort()
        if ivars:
            lines.append(p.y)
            p.y += 1

        for varname in ivars:
            item = self.canvas.offset_text(p, varname, tags=tags)
            p.y += 1

        # draw the box
        bbox = self.get_bbox()
        item = self.canvas.box(bbox, tags=tags, **self.boxoptions)
        self.boxitem = item

        # draw the lines
        for y in lines:
            coords = [[bbox.left, y], [bbox.right, y]]
            item = self.canvas.line(coords, tags=tags, **self.lineoptions)

        # only the things we have drawn so far should be bound
        self.bind()

        # make a list of all classes drawn
        alldrawn = [self]

        # draw the descendents of this class
        childs = self.cls.childs

        if childs:
            q = pos.copy()
            q.x = bbox.right + 8
            
            drawn = self.diag.draw_classes(childs, q, tags)
            alldrawn.extend(drawn)

            self.head = self.arrow_head(diag, bbox, tags)

            # connect this class to its children
            for child in childs:
                a = ParentArrow(self.lumpy, self, child.cdc)
                self.diag.add_arrow(a)

        # if the class is not in the right position, shift it.
        dx = pos.x - self.get_bbox().left
        self.canvas.move(self.tags, dx, 0)

        return alldrawn

    def arrow_head(self, diag, bbox, tags, size=0.5):
        """Draws the hollow arrow head.
        
        Connects this class to classes that inherit from it.
        """
        x, y = bbox.midright()
        x += 0.1
        coords = [[x, y], [x+size, y+size], [x+size, y-size], [x, y]]
        item = self.canvas.line(coords, tags=tags, **self.lineoptions)
        return item


class Binding(Thing):
    """Represents the binding between a key or variable and a value."""
    def __init__(self, lumpy, key, val):
        lumpy.register(self, (key, val))
        self.key = key
        self.vals = [val]

    def rebind(self, val):
        """Add to the list of values.

        I don't remember what this is for and it is not in current use.
        """
        self.vals.append(val)

    def draw_key(self, diag, pos, flip, tags):
        """Draws a reference to a previously-drawn key.

        (Rather than drawing the key inside the mapping.)
        """
        pos.x -= 0.5 * flip
        self.dot2 = Dot()
        self.dot2.draw(diag, pos, -flip, tags=tags)

        # only the things we have drawn so far should
        # be handles for this binding
        self.bind()

        if not self.key.isdrawn():
            pos.x -= 2.0 * flip
            self.key.draw(diag, pos, -flip, tags=tags)

        a = ReferenceArrow(self.lumpy, self.dot2, self.key, fill='orange')
        diag.add_arrow(a)
        
    def drawme(self, diag, pos, flip, tags=tuple()):
        """Draws the Thing."""
        self.dot = Dot()
        self.dot.draw(diag, pos, flip, tags=tags)
        
        p = pos.copy()
        p.x -= 0.5 * flip

        # if the key is a Simple, try to draw it inside the mapping;
        # otherwise, draw a reference to it
        if isinstance(self.key, Simple):
            drawn = self.key.draw(diag, p, -flip, tags=tags)

            # if a Simple thing doesn't get drawn, we must be in
            # pedantic mode.
            if drawn:
                self.bind()
                self.dot2 = None
            else:
                self.draw_key(diag, p, flip, tags)                
        else:
            self.draw_key(diag, p, flip, tags)                

        p = pos.copy()
        p.x += 2.0 * flip

        for val in self.vals:
            val.draw(diag, p, flip, tags=tags)
            a = ReferenceArrow(self.lumpy, self.dot, val, fill='orange')
            diag.add_arrow(a)
            p.y += 1


class Arrow(Thing):
    """Parent class for arrows."""
    def update(self):
        """Redraws this arrow after something moves."""
        if not hasdiag(self):
            return
        self.diag.canvas.delete(self.item)
        self.draw(self.diag)

    

class ReferenceArrow(Arrow):
    """Represents a reference in an object diagram."""
    def __init__(self, lumpy, key, val, **options):
        self.lumpy = lumpy
        self.key = key
        self.val = val
        self.options = options
        
    def draw(self, diag):
        """Draw the Thing.

        Overrides draw() rather than drawme() because arrows can't
        be dragged and dropped.
        """
        self.diag = diag
        canvas = diag.canvas
        self.item = canvas.arrow(self.key.pos(),
                                 self.val.pos(),
                                 **self.options)
        self.item.lower()

    def update(self):
        """Redraws this arrow after something moves."""
        if not hasdiag(self):
            return
        self.item.coords([self.key.pos(), self.val.pos()])


class ParentArrow(Arrow):
    """Represents an inheritance arrow.

    Shows an is-a relationship between classes in a class diagram.
    """
    def __init__(self, lumpy, parent, child, **options):
        self.lumpy = lumpy
        self.parent = parent
        self.child = child
        underride(options, fill='blue')
        self.options = options
        
    def draw(self, diag):
        """Draw the Thing.

        Overrides draw() rather than drawme() because arrows can't
        be dragged and dropped.
        """
        self.diag = diag
        parent, child = self.parent, self.child

        # the line connects the midleft point of the child
        # to the arrowhead of the parent; it always contains
        # two horizontal segments and one vertical.
        canvas = diag.canvas
        bbox = canvas.bbox(parent.head)
        p = bbox.midright()
        q = canvas.bbox(child.boxitem).midleft()
        midx = (p.x + q.x) / 2.0
        m1 = [midx, p.y]
        m2 = [midx, q.y]
        coords = [p, m1, m2, q]
        self.item = canvas.line(coords, **self.options)
        canvas.lower(self.item)


class ContainsArrow(Arrow):
    """Represents a contains arrow.

    Shows a has-a relationship between classes in a class diagram.
    """
    def __init__(self, lumpy, parent, child, **options):
        self.lumpy = lumpy
        self.parent = parent
        self.child = child
        underride(options, fill='orange', arrow=LAST)
        self.options = options
        
    def draw(self, diag):
        """Draw the Thing.

        Overrides draw() rather than drawme() because arrows can't
        be dragged and dropped.
        """
        self.diag = diag
        parent, child = self.parent, self.child

        if not child.isdrawn():
            self.item = None
            return
        
        canvas = diag.canvas
        p = canvas.bbox(parent.boxitem).midleft()
        q = canvas.bbox(child.boxitem).midright()
        coords = [p, q]
        self.item = canvas.line(coords, **self.options)
        canvas.lower(self.item)


class Stack(Thing):
    """Represents the call stack."""
    def __init__(self, lumpy, snapshot):
        self.lumpy = lumpy
        self.frames = [Frame(lumpy, frame) for frame in snapshot.frames]
    
    def drawme(self, diag, pos, flip, tags=tuple()):
        """Draws the Thing."""
        p = pos.copy()
        
        for frame in self.frames:
            frame.draw(diag, p, flip, tags=tags)

            bbox = self.get_bbox()
            #p.y = bbox.bottom + 3
            p.x = bbox.right + 3


def make_bindings(lumpy, iterator):
    """Make bindings for each key-value pair in iterator.

    The keys are made into Index objects.
    """
    seq = [Binding(lumpy, Index(lumpy, k), make_thing(lumpy, v))
           for k, v in iterator]
    return seq


def make_kvps(lumpy, iterator):
    """Make bindings for each key-value pair in iterator.
    
    The keys are made into Thing objects.
    """
    seq = [Binding(lumpy, make_thing(lumpy, k), make_thing(lumpy, v))
           for k, v in iterator]
    return seq


def make_thing(lumpy, val):
    """Make a Thing to represents this value.

    Either by making a new one or looking up an existing one.
    """
    # if we're being pedantic, then we always show aliased
    # values
    if lumpy.pedantic:
        thing = lumpy.lookup(val)
        if thing != None:
            return thing

    # otherwise for simple immutable types, ignore aliasing and
    # just draw
    simple = (str, bool, int, int, float, complex, type(None))

    if isinstance(val, simple):
        thing = Simple(lumpy, val)
        return thing

    # now check for aliasing even if we're not pedantic
    thing = lumpy.lookup(val)
    if thing != None:
        return thing

    # check the type of the value and dispatch accordingly
    if type(val) == type(Lumpy) or type(val) == type(type(int)):
        thing = Class(lumpy, val)  
    elif hasdict(val) or hasslots(val):
        thing = Instance(lumpy, val)
    elif isinstance(val, (list, tuple)):
        thing = Sequence(lumpy, val)
    elif isinstance(val, dict):
        thing = Mapping(lumpy, val)
    elif isinstance(val, object):
        thing = Instance(lumpy, val)
    else:
        # print "Couldn't classify", val, type(val)
        thing = Simple(lumpy, val)

    return thing


# the following are short functions that check for certain attributes
def hasname(obj): return hasattr(obj, '__name__')
def hasclass(obj): return hasattr(obj, '__class__')
def hasdict(obj): return hasattr(obj, '__dict__')
def hasslots(obj): return hasattr(obj, '__slots__')
def hasdiag(obj): return hasattr(obj, 'diag')
def iscallable(obj): return hasattr(obj, '__call__')


class Snapframe(object):
    """A snapshot of a call frame."""
    def __init__(self, tup):
        frame, filename, lineno, self.func, lines, index = tup
        (self.arg_names,
         self.args,
         self.kwds,
         locs) = inspect.getargvalues(frame)

        # make a copy of the dictionary of local vars
        self.locals = dict(locs)

        # the function name for the top-most frame is __main__
        if self.func == '?':
            self.func = '__main__'

    def subtract(self, other):
        """Deletes the keys in other from self."""
        for key in other.locals:
            try:
                del self.locals[key]
            except KeyError:
                print(key, "this shouldn't happen")


class Snapshot(object):
    """A snapshot of the call stack."""

    def __init__(self):
        """Converts from the format returned by inspect to a list of frames.

        Drop the last three frames,
        which are the Lumpy functions object_diagram, make_stack,
        and Stack.__init__
        """
        st = inspect.stack()
        frames = [Snapframe(tup) for tup in st[3:]]
        frames.reverse()
        self.frames = frames

    def spew(self):
        """Prints the frames in this snapshot."""
        for frame in self.frames:
            print(frame.func, frame)

    def clean(self, ref):
        """Remove all the variables in the reference stack from self.

        NOTE: This currently only works on the top-most frame
        """
        f1 = self.frames[0]
        f2 = ref.frames[0]
        f1.subtract(f2)
                    

class Lumpy(Gui):
    """Container for the program state and its representations."""

    def __init__(self, debug=False, pedantic=False):
        """Initializes Lumpy.

        Args:
            debug: boolean that makes the outlines of the frames visible.
            pedantic: boolean whether to show aliasing for simple values.

        If pedantic is false, simple values are replicated, rather
        than, for example, having all references to 1 refer to the
        same int object.
        """
        Gui.__init__(self, debug)
        self.pedantic = pedantic
        self.withdraw()

        # initially there is no object diagram, no class diagram
        # and no representation of the stack.
        self.od = None
        self.cd = None
        self.stack = None

        # instance_vars maps from classes to the instance vars
        # that are drawn for that class; for opaque classes, it
        # is an empty list.

        # an instance of an opaque class is shown with a small empty box;
        # the contents are not shown.
        self.instance_vars = {}

        # the following classes are opaque by default
        self.opaque_class(Lumpy)
        self.opaque_class(object)
        self.opaque_class(type(make_thing))    # function
        self.opaque_class(Exception)
        self.opaque_class(set)                 # I don't remember why

        # any object that belongs to a class in the Tkinter module
        # is opaque (the name of the module depends on the Python version)
        self.opaque_module(TKINTER_MODULE)

        # by default, class objects and module objects are opaque
        classobjtype = type(Lumpy)
        self.opaque_class(classobjtype)
        modtype = type(inspect)
        self.opaque_class(modtype)

        # the __class__ of a new-style object is a type object.
        # when type objects are drawn, show only the __name__
        self.opaque_class(type)

        self.make_reference()

    def restrict_class(self, classobj, variables=None):
        """Restricts a class so that only the given variables are shown."""
        if variables == None:
            variables = []
        self.instance_vars[classobj] = variables

    def opaque_class(self, classobj):
        """Restricts a class so that no variables are shown."""
        self.restrict_class(classobj, None)

    def is_opaque(self, classobj):
        """Checks whether this class is completely opaque.

        (restricted to _no_ instance variables)
        """
        try:
            return not len(self.instance_vars[classobj])
        except KeyError:
            return False

    def transparent_class(self, classobj):
        """Unrestricts a class so its variables are shown.

        If the class is not restricted, raise an exception."""
        del self.instance_vars[classobj]
        
    def opaque_module(self, modobj):
        """Makes all classes defined in this module opaque."""
        for var, val in modobj.__dict__.items():
            if isinstance(val, type(Lumpy)):
                self.opaque_class(val)

    def make_reference(self):
        """Takes a snapshot of the current state.

        Subsequent diagrams will be relative to this reference.
        """
        self._make_reference_helper()

    def _make_reference_helper(self):
        """Takes the reference snapshot.

        This extra method call is here so that the reference
        and the snapshot we take later have the same number of
        frames on the stack.  UGH.
        """
        self.ref = Snapshot()

    def make_stack(self):
        """Takes a snapshot of the current state.

        Subtract away the frames and variables that existed in the
        previous reference, then makes a Stack.
        """
        self.snapshot = Snapshot()
        self.snapshot.clean(self.ref)
        
        self.values = {}
        self.classes = []
        self.stack = Stack(self, self.snapshot)
                
    def register(self, thing, val):
        """Associates a value with the Thing that represents it.

        Later we can check whether we have already created
        a Thing for a given value.
        """
        thing.lumpy = self
        thing.val = val
        self.values[id(val)] = thing
    
    def lookup(self, val):
        """Check whether a value is already represented by a Thing.

        Returns:
            an existing Thing or None.
        """
        vid = id(val)
        return self.values.get(vid, None)

    def object_diagram(self, obj=None, loop=True):
        """Creates a new object diagram based on the current state.

        If an object is provided, draws the object.  Otherwise, draws
        the current run-time stack (relative to the last reference).
        """
        if obj:
            thing = make_thing(self, obj)
        else:
            if self.stack == None:
                self.make_stack()
            thing = self.stack

        # if there is already an Object Diagram, clear it; otherwise,
        # create one
        if self.od:
            self.od.clear()
        else:
            self.od = ObjectDiagram(self)

        # draw the object or stack, then the arrows
        drawn = self.od.draw(thing)
        self.od.draw_arrows()

        # wait for the user
        if loop:
            self.mainloop()

        return Thing.things_drawn

    def class_diagram(self, classes=None, loop=True):
        """Create a new object diagram based on the current state.

        If a list of classes is provided, only those classes are
        shown.  Otherwise, all classes that Lumpy know about are shown.
        """

        # if there is not already a snapshot, make one
        if self.stack == None:
            self.make_stack()

        # scan the the stack looking for has-a
        # relationships (note that we can't do this until the
        # stack is complete)
        for val in list(self.values.values()):
            if isinstance(val, Instance) and val.cls is not None:
                val.scan_bindings(val.cls)
            
        # if there is already a class diagram, clear it; otherwise
        # create one
        if self.cd:
            self.cd.clear()
        else:
            self.cd = ClassDiagram(self, classes)

        self.cd.draw()

        if loop:
            self.mainloop()

        return Thing.things_drawn

    def get_class_list(self):
        """Returns list of classes that should be drawn in a class diagram."""
        t = []
        for cls in self.classes:
            if not self.is_opaque(cls.classobj):
                t.append(cls)
            elif cls.parents or cls.childs:
                t.append(cls)
        return t


class Diagram(object):
    """Parent class for ClassDiagram and ObjectDiagram."""
    def __init__(self, lumpy, title):
        self.lumpy = lumpy
        self.arrows = []

        self.tl = lumpy.tl()
        self.tl.title(title)
        self.tl.geometry('+0+0')
        self.tl.protocol("WM_DELETE_WINDOW", self.close)
        self.setup()

    def ca(self, width=100, height=100, **options):
        """make a canvas for the diagram"""
        return self.lumpy.widget(DiagCanvas, width=width, height=height,
                                 **options)
        
    def setup(self):
        """create the gui for the diagram"""

        # push the frame for the toplevel window
        self.lumpy.pushfr(self.tl)
        self.lumpy.col([0, 1])

        # the frame at the top contains buttons
        self.lumpy.row([0, 0, 1], bg='white')
        self.lumpy.bu(text='Close', command=self.close)
        self.lumpy.bu(text='Print to file:', command=self.printfile_callback)
        self.en = self.lumpy.en(width=10, text='lumpy.ps')
        self.en.bind('<Return>', self.printfile_callback)
        self.la = self.lumpy.la(width=40)
        self.lumpy.endrow()

        # the grid contains the canvas and scrollbars
        self.lumpy.gr(2, [1, 0])
        
        self.ca_width = 1000
        self.ca_height = 500
        self.canvas = self.ca(self.ca_width, self.ca_height, bg='white')

        yb = self.lumpy.sb(command=self.canvas.yview, sticky=N+S)
        xb = self.lumpy.sb(command=self.canvas.xview, orient=HORIZONTAL,
                         sticky=E+W)
        self.canvas.configure(xscrollcommand=xb.set, yscrollcommand=yb.set,
                              scrollregion=(0, 0, 800, 800))
        
        self.lumpy.endgr()
        self.lumpy.endcol()
        self.lumpy.popfr()

        # measure some sample letters to get the text height
        # and set the scale factor for the canvas accordingly
        self.canvas.clear_transforms()
        bbox = self.canvas.measure(['bdfhklgjpqy'])
        self.unit = 1.0 * bbox.height()
        transform = ScaleTransform([self.unit, self.unit])
        self.canvas.add_transform(transform)
        

    def printfile_callback(self, event=None):
        """Dumps the contents of the canvas to a file.

        Gets the filename from the filename entry.
        """
        filename = self.en.get()
        self.printfile(filename)

    def printfile(self, filename):
        """Dumps the contents of the canvas to a file.

        filename: string output file name
        """
        # shrinkwrap the canvas
        bbox = self.canvas.bbox(ALL)
        width = bbox.right*self.unit
        height = bbox.bottom*self.unit
        self.canvas.config(width=width, height=height)

        # write the file
        self.canvas.dump(filename)
        self.canvas.config(width=self.ca_width, height=self.ca_height)
        self.la.config(text='Wrote file ' + filename)
        
    def close(self):
        """close the window and exit"""
        self.tl.withdraw()
        self.lumpy.quit()

    def add_arrow(self, arrow):
        """append a new arrow on the list"""
        self.arrows.append(arrow)

    def draw_arrows(self):
        """draw all the arrows on the list"""
        for arrow in self.arrows:
            arrow.draw(self)

    def update_arrows(self, n=None):
        """update up to n arrows (or all of them is n==None)"""
        i = 0
        for arrow in self.arrows:
            arrow.update()
            i += 1
            if n and i > n: break


class ObjectDiagram(Diagram):
    """Represents an object diagram."""

    def __init__(self, lumpy=None):
        Diagram.__init__(self, lumpy, 'Object Diagram')

    def draw(self, thing):
        """Draws the top-level Thing."""
        drawn = thing.draw(self, Point([2, 2]), flip=1)

        # configure the scroll region
        self.canvas.scroll_config()
        return drawn

    def clear(self):
        """Clears the diagram."""
        self.arrows = []
        self.tl.deiconify()
        self.canvas.delete(ALL)


class ClassDiagram(Diagram):
    """Represents a class diagram."""

    def __init__(self, lumpy, classes=None):
        Diagram.__init__(self, lumpy, 'Class Diagram')
        self.classes = classes

    def draw(self):
        """Draw the class diagram.

        Includes the classes in self.classes,
        or if there are none, then all the classes Lumpy has seen.
        """
        pos = Point([2, 2])

        if self.classes == None:
            classes = self.lumpy.get_class_list()
        else:
            classes = [make_thing(self.lumpy, cls) for cls in self.classes]

        # find the classes that have no parents, and find the
        # height of each tree
        roots = [c for c in classes if c.parents == []]
        for root in roots:
            root.set_height()

        # for all the leaf nodes, compute the distance to
        # the parent
        leafs = [c for c in classes if c.childs == []]
        for leaf in leafs:
            leaf.set_depth()

        # if we're drawing all the classes, start with the roots;
        # otherwise draw the classes we were given.
        if self.classes == None:
            drawn = self.draw_classes(roots, pos)
        else:
            drawn = self.draw_classes(classes, pos)
            
        self.draw_arrows()

        # configure the scroll region
        self.canvas.scroll_config()

    def draw_classes(self, classes, pos, tags=tuple()):
        """Draw this list of classes and all their subclasses.

        Starts at the given position.

        Returns:
            list of all classes drawn
        """
        p = pos.copy()
        alldrawn = []

        for c in classes:
            drawn = c.cdc.draw(self, p, tags)
            alldrawn.extend(drawn)

            # TODO: change this so it finds the bottom-most bbox in drawn
            bbox = c.cdc.get_bbox()
            
            for thing in alldrawn:
                if thing is not c:
                    # can't use bbox.union because it assumes that
                    # the positive y direction is UP
                    bbox = union(bbox, thing.get_bbox())
            
            p.y = bbox.bottom + 2

        for c in classes:
            for d in c.refers:
                a = ContainsArrow(self.lumpy, c.cdc, d.cdc)
                self.arrows.append(a)

        return alldrawn


def union(one, other):
    """Returns a new bbox that covers one and other.

    Assumes that the positive y direction is DOWN.
    """
    left = min(one.left, other.left)
    right = max(one.right, other.right)
    top = min(one.top, other.top)
    bottom = max(one.bottom, other.bottom)
    return BBox([[left, top], [right, bottom]])



###########################
# test code below this line
###########################

def main(script, *args, **kwds):
    class Cell:
        def __init__(self, car=None, cdr=None):
            self.car = car
            self.cdr = cdr

        def __hash__(self):
            return hash(self.car) ^ hash(self.cdr)

    def func_a(x):
        t = [1, 2, 3]
        t.append(t)
        y = None
        z = 1
        long_name = 'allen'
        d = dict(a=1, b=2)

        func_b(x, y, t, long_name)

    def func_b(a, b, s, name):
        d = dict(a=1, b=(1, 2, 3))
        cell = Cell()
        cell.car = 1
        cell.cdr = cell
        func_c()

    def func_c():
        t = (1, 2)
        c = Cell(1, Cell())
        d = {}
        d[c] = 7
        d[7] = t
        d[t] = c.cdr
        LUMPY.object_diagram()

    func_a(17)


if __name__ == '__main__':
    LUMPY = Lumpy()
    LUMPY.make_reference()
    main(*sys.argv)
