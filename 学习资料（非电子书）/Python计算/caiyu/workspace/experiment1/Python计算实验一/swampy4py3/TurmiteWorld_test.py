"""This module is part of Swampy, a suite of programs available from
allendowney.com/swampy.

Copyright 2010 Allen B. Downey
Distributed under the GNU General Public License at gnu.org/licenses/gpl.html.
"""

import unittest

import TurmiteWorld

class Tests(unittest.TestCase):

    def test_turmite_world(self):
        tw = TurmiteWorld.TurmiteWorld()
        tw.setup()
        turmite = tw.make_turmite()
        tw.clear()
        tw.quit()
        
    def test_turmite(self):
        tw = TurmiteWorld.TurmiteWorld()
        t = TurmiteWorld.Turmite(tw)
        t.draw()
        t.fd()
        t.bk()
        t.rt()
        t.lt()
        cell = t.get_cell()
        t.step()
        t.undraw()
        tw.quit()

if __name__ == '__main__':
    unittest.main()
