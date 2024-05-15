"""This module is part of Swampy, a suite of programs available from
allendowney.com/swampy.

Copyright 2011 Allen B. Downey
Distributed under the GNU General Public License at gnu.org/licenses/gpl.html.
"""

import unittest

import CellWorld

class Tests(unittest.TestCase):

    def test_cell_world(self):
        cw = CellWorld.CellWorld(cell_size=10, interactive=True)
        cw.bind()

        cell = cw.make_cell(2, 3)
        got = cw.get_cell(2, 3)
        self.assertTrue(cell is got)

        neighbors = cw.get_four_neighbors(cell)
        self.assertEqual(len(neighbors), 4)

        neighbors = cw.get_eight_neighbors(cell)
        self.assertEqual(len(neighbors), 8)

        cw.rescale()

        cw.clear()
        cw.quit()
        
    def test_cell(self):
        cw = CellWorld.CellWorld(cell_size=10, interactive=True)
        cell = cw.make_cell(2, 3)

        tag = cell.draw()

        cell.config(fill='red')

        option = cell.get_config('fill')
        self.assertEqual(option, 'red')

        cell.mark()
        self.assertTrue(cell.is_marked())

        cell.unmark()
        self.assertFalse(cell.is_marked())

        cell.toggle()
        self.assertTrue(cell.is_marked())

        cell.undraw()

if __name__ == '__main__':
    unittest.main()
