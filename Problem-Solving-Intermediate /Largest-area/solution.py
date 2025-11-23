"""
URL: https://github.com/not-brajesh
Author: Brajesh Kumar
"""

import sys

class SegmentTree:
    def __init__(self, start, end):
        self.start = start
        self.end = end
        self.left_child = None
        self.right_child = None
        self.max_gap = end - start
    
    def cut(self, position):
        if position <= self.start or position >= self.end:
            return
        
        if self.left_child is not None:
            if position < self.left_child.end:
                self.left_child.cut(position)
            else:
                self.right_child.cut(position)
            self.max_gap = max(self.left_child.max_gap, self.right_child.max_gap)
        else:
            self.left_child = SegmentTree(self.start, position)
            self.right_child = SegmentTree(position, self.end)
            self.max_gap = max(position - self.start, self.end - position)

def getMaxArea(width, height, isVertical, distance):
    width_tree = SegmentTree(0, width)
    height_tree = SegmentTree(0, height)
    
    results = []
    
    for i in range(len(isVertical)):
        if isVertical[i]:
            width_tree.cut(distance[i])
        else:
            height_tree.cut(distance[i])
        
        max_area = width_tree.max_gap * height_tree.max_gap
        results.append(max_area)
    
    return results

def main():
    w = int(input().strip())
    h = int(input().strip())
    
    n_vertical = int(input().strip())
    vertical_cuts = []
    for _ in range(n_vertical):
        vertical_cuts.append(int(input().strip()) != 0)
    
    n_distance = int(input().strip())
    distances = []
    for _ in range(n_distance):
        distances.append(int(input().strip()))
    
    result = getMaxArea(w, h, vertical_cuts, distances)
    
    for area in result:
        print(area)

if __name__ == '__main__':
    main()
