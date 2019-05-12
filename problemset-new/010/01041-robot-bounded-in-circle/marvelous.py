DIR = [(0, 1), (-1, 0), (0, -1), (1, 0)]
class Solution:
    def isRobotBounded(self, instructions: str) -> bool:
        x, y = 0, 0
        d_idx = 0
        circled = False
        for i in range(4):
            for op in instructions:
                if op == 'G':
                    x, y = x + DIR[d_idx][0], y + DIR[d_idx][1]
                elif op == 'L':
                    d_idx = (d_idx + 1) % 4
                else:
                    d_idx = (d_idx + 3) % 4 
            if x == y == 0:
                circled = True
                break
        return circled        
