class Solution:
    def getHint(self, secret: str, guess: str) -> str:
        success, fail = 0, 0
        t1, t2 = [0] * 10, [0] * 10
        for cs, cg in zip(secret, guess):
            if cs == cg:
                success += 1
                continue
            t1[ord(cs) - 48] += 1
            t2[ord(cg) - 48] += 1
            
        for v1, v2 in zip(t1, t2):
            fail += min(v1, v2)
        
        return '{}A{}B'.format(success, fail)
