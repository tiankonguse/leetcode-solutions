import math
import turtle


class State:
    def __init__(self, t):
        self.x = t.xcor()
        self.y = t.ycor()
        self.heading = t.heading()
        self.pensize = t.pensize()
        self.pencolor = t.pencolor()

    def Recover(s, t):
        t.penup()
        t.setx(s.x)
        t.sety(s.y)
        t.setheading(s.heading)
        t.pensize(s.pensize)
        t.pencolor(s.pencolor)
        t.pendown()
        return


class Stack:
    def __init__(self, t):
        self.t = t
        self.stack = []

    def SaveState(self):
        self.stack.append(State(self.t))

    def RecoverState(self):
        s = self.stack.pop()
        s.Recover(self.t)


class Graph:
    def __init__(self, t, s, r, d, X, Y):
        self.t = t
        self.s = s
        self.r = r
        self.d = d
        self.X = X
        self.Y = Y

    def ReInit(self, X, Y):
        self.X = X
        self.Y = Y

    def MoveTo(self, x, y):
        self.t.penup()
        self.t.goto(x + self.X, y + self.Y)
        self.t.pendown()

    def innerMoveTo(self, x, y):
        self.t.penup()
        self.t.goto(x, y)
        self.t.pendown()

    def DrawLine(self, x, y, dir, step):
        self.MoveTo(x, y)
        self.t.seth(dir)
        self.t.fd(step)

    def innerDrawLine(self, x, y, dir, step):
        self.innerMoveTo(x, y)
        self.t.seth(dir)
        self.t.fd(step)

    def DrawCircle(self, radius, extent):
        p1 = self.t.pos()
        self.t.circle(radius, extent)
        p2 = self.t.pos()
        self.innerDrawCircleRadius(p1, p2)

    def DrawXY(self):
        if self.d.open():
            return
        self.s.SaveState()
        self.t.pensize(1)
        self.t.pencolor("gray")
        for i in range(4):
            self.innerDrawLine(self.X, self.Y, i * 90, self.r*10)
        self.s.RecoverState()

    def DrawCircleTangent(self):  # 切线
        if self.d.open():
            return
        self.s.SaveState()
        self.t.pensize(1)
        self.t.pencolor("red")
        self.innerDrawDoubleLine(
            self.t.xcor(), self.t.ycor(), self.t.heading())
        self.s.RecoverState()

    def innerDrawDoubleLine(self, x, y, heading):
        if self.d.open():
            return
        self.innerDrawLine(x, y, heading, 10 * self.r)
        self.innerDrawLine(x, y, 180 + heading, 10 * self.r)

    def GetDir(self, p1, p2):
        angle = math.atan2(p1[1]-p2[1], p1[0]-p2[0])
        return angle*(180 / math.pi)

    def GetDis(self, p1, p2):
        x = p1[0] - p2[0]
        y = p1[1] - p2[1]
        return math.sqrt(x * x + y * y)

    def innerDrawCircleRadius(self, p1, p2):
        if self.d.open():
            return
        dir = self.GetDir(p1, p2)
        self.s.SaveState()
        self.t.pensize(1)
        self.t.pencolor("red")
        self.innerDrawDoubleLine((p1[0]+p2[0])/2, (p1[1]+p2[1])/2, dir+90)
        self.innerDrawDoubleLine(p1[0], p1[1], dir)
        self.s.RecoverState()

    def DrawDoubleDot(self, x, y, r):
        self.MoveTo(-x, y)
        self.t.dot(r)
        self.MoveTo(x, y)
        self.t.dot(r)

    def GetCircleCenter(self, r):
        self.s.SaveState()
        self.t.penup()
        self.t.left(90)
        self.t.fd(r)
        pos = self.t.pos()
        self.t.pendown()
        self.s.RecoverState()
        return pos


class Debug:
    flag_ = 0

    def open(self):
        return self.flag_ == 0


class Card:
    t = turtle

    def __init__(self, x=0, y=0, f=100, c="black", s="fastest"):
        self.F = f
        self.C = c
        self.speed = s
        self.s = Stack(self.t)
        self.d = Debug()
        self.g = Graph(self.t, self.s, self.F, self.d, x, y)

    def Draw(self):
        self.Init()
        self.DrawOutline()
        self.DrawHair()
        self.DrawEye()
        self.DrawMouth()
        self.DrawCheek()

    def Init(self):  # 画板 6:4
        self.t.pensize(5)
        self.t.pencolor(self.C)
        self.t.speed(self.speed)
        self.g.DrawXY()

    def SetUp(self, x, y):
        self.t.setup(6 * self.F * x, 4 * self.F * y)

    def ReInit(self, X, Y):
        self.g.ReInit(X * 6 * self.F, Y * 4 * self.F)

    def Wait(self):
        self.t.ht()
        self.t.done()

    def DrawOutline(self):
        self.g.MoveTo(-1.72 * self.F, -0.8 * self.F)
        # 下半部轮廓
        self.t.seth(-20)
        self.g.DrawCircleTangent()
        self.g.DrawCircle(5 * self.F, 20 * 2)
        self.g.DrawCircleTangent()
        # print(self.g.GetCircleCenter(5 * self.F))

        # 上半部轮廓
        self.t.seth(90 + 20)
        self.g.DrawCircleTangent()
        self.R = 1.82 * self.F
        self.g.DrawCircle(self.R, 2 * (90 - 20))
        # print(self.g.GetCircleCenter(self.R))
        self.center = self.g.GetCircleCenter(self.R)
        self.g.DrawCircleTangent()

    def DrawHair(self):
        self.t.seth(148)
        centers = []
        r = 0.19 * self.F
        for i in range(6):
            self.g.DrawCircleTangent()
            self.g.DrawCircle(-0.33 * self.F, 140)
            if i < 5:
                self.g.DrawCircleTangent()
                self.t.circle(r, 109/2)
                centers.append((self.g.GetCircleCenter(r), self.t.heading() - 90))
                self.t.circle(r, 109/2)


        R = 1.82 * self.F
        for p in centers:
            pos = p[0]
            dir = p[1]
            dis = self.g.GetDis(pos, self.center)
            self.t.penup()
            self.t.goto(pos[0], pos[1])
            self.t.seth(dir)
            self.t.fd(r)
            self.t.pendown()
            self.t.fd(dis - r - R)

    def DrawEye(self):
        self.g.DrawDoubleDot(0.38 * self.F, 0, 0.20 * self.F)

    def DrawMouth(self):
        self.g.DrawLine(-0.15 * self.F, -0.3 * self.F, 3, 0.3 * self.F)
        self.t.seth(70)
        self.g.DrawCircleTangent()
        self.g.DrawCircle(0.18 * self.F, -125)
        self.g.DrawCircleTangent()

    def DrawCheek(self):
        self.t.pencolor("#f8bbd0")
        self.g.DrawDoubleDot(-0.45 * self.F, -0.2 * self.F, 0.23 * self.F)


c = Card(0, 0, 200)
X = 1
Y = 1
c.SetUp(X, Y)
for x in range(X):
    for y in range(Y):
        c.ReInit(x + 0.5 - X/2, y + 0.5 - Y/2)
        c.Draw()
c.Wait()
