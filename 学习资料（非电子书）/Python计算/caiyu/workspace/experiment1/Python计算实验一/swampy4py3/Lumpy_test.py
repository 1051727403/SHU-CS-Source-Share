"""This module is part of Swampy, a suite of programs available from
allendowney.com/swampy.

Copyright 2011 Allen B. Downey
Distributed under the GNU General Public License at gnu.org/licenses/gpl.html.
"""

import unittest

import Lumpy

class Tests(unittest.TestCase):

    def test_lumpy(self):
        lumpy = Lumpy.Lumpy()
        lumpy.restrict_class(Tests)
        lumpy.opaque_class(Tests)
        self.assertTrue(lumpy.is_opaque(Tests))

        lumpy.transparent_class(Tests)
        self.assertFalse(lumpy.is_opaque(Tests))

        lumpy.opaque_module(unittest)

        things_drawn = lumpy.object_diagram(loop=False)
        self.assertTrue(things_drawn > 200)

        things_drawn = lumpy.class_diagram(loop=False)
        self.assertTrue(things_drawn > 200)

if __name__ == '__main__':
    unittest.main()
