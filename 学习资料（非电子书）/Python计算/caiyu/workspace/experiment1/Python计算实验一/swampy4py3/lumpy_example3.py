#!/usr/bin/python

import Lumpy
lumpy = Lumpy.Lumpy()

# if you don't make a reference after instantiating
# Lumpy, the local variable lumpy is visible.  Even
# so, the Lumpy class is opaque by default, so we
# have to make it transparent.
lumpy.transparent_class(Lumpy.Lumpy)

lumpy.class_diagram()

