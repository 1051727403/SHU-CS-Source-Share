#!/usr/bin/python

"""
This module is part of Swampy, a suite of programs available from
allendowney.com/swampy.

Copyright 2005 Allen B. Downey
Distributed under the GNU General Public License at gnu.org/licenses/gpl.html.

"""

# create a Lumpy object and capture reference state
import Lumpy
lumpy = Lumpy.Lumpy()
lumpy.make_reference()

# run the test code
x = [1, 2, 3]
y = x
z = list(x)

# draw the current state (relative to the last reference)
lumpy.object_diagram()

