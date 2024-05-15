"""This example is part of Swampy, a suite of programs available from
allendowney.com/swampy.

Copyright 2011 Allen B. Downey
Distributed under the GNU General Public License at gnu.org/licenses/gpl.html.
"""

def draw(t, length, n):
    """Draws a tree with the given trunk length and levels of recursion.

    Turtle ends up back where he started.

    Args:
        t: Turtle
        length: trunk length
        n: int levels of recursion
    """
    if n == 0:
        return
    angle = 50
    fd(t, length*n)
    lt(t, angle)
    draw(t, length, n-1)
    rt(t, 2*angle)
    draw(t, length, n-1)
    lt(t, angle)
    bk(t, length*n)

bob = Turtle()
bob.delay = 0.01
lt(bob)
bk(bob, 70)
draw(bob, 10, 7)
