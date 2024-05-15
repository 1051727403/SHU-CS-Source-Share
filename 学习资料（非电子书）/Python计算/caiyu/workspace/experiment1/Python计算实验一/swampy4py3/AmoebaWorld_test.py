"""This module is part of Swampy, a suite of programs available from
allendowney.com/swampy.

Copyright 2011 Allen B. Downey
Distributed under the GNU General Public License at gnu.org/licenses/gpl.html.
"""

import unittest

import AmoebaWorld

class Tests(unittest.TestCase):

    def test_amoeba_world(self):
        aw = AmoebaWorld.AmoebaWorld(interactive=True)
        a = AmoebaWorld.Amoeba()
        aw.set_end_time('3.14')
        aw.set_x_t('2*t')
        aw.set_y_t('3*t')
        aw.run()
        aw.clear()
        aw.quit()
        
    def test_amoeba(self):
        aw = AmoebaWorld.AmoebaWorld()
        a = AmoebaWorld.Amoeba()
        a.draw()
        a.move(2, 3)
        aw.quit()

if __name__ == '__main__':
    unittest.main()
