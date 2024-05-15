#!/usr/bin/python

"""
This module is part of Swampy, a suite of programs available from
allendowney.com/swampy.

Copyright 2005 Allen B. Downey
Distributed under the GNU General Public License at gnu.org/licenses/gpl.html.

"""

import World
from TurtleWorld import TurtleWorld, Turtle

import Lumpy
lumpy = Lumpy.Lumpy()
lumpy.opaque_class(World.Interpreter)
lumpy.make_reference()

world = TurtleWorld()
bob = Turtle(world)

lumpy.object_diagram()
lumpy.class_diagram()

