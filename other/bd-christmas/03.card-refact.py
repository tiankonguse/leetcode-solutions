import turtle as t

def MoveTo(x, y):
    t.penup()
    t.goto(x, y)
    t.pendown()
def DrawLine(x, y, dir, step):
    MoveTo(x, y)
    t.seth(dir)
    t.fd(step)
def DrawDoubleDot(x, y, r):
    MoveTo(-x, y)
    t.dot(r)
    MoveTo(x, y)
    t.dot(r)

def Init():
    t.setup(600, 400)
    t.pensize(5)
    t.pencolor("black")
def DrawOutline():
    MoveTo(-180, -80)
    # 下半部轮廓
    t.seth(-20)
    t.circle(500, 20 * 2)
    # 上半部轮廓
    t.seth(90 + 20)
    t.circle(182, 2 * (90 - 20))
def DrawHair():
    t.seth(150)
    # 6 个大弧形 + 5 个小弧形
    for i in range(4):
        t.circle(-35, 143)
        t.circle(19, 110)

    t.circle(-35, 135)
    t.left(5)
    t.circle(19, 100)
    t.circle(-24.5, 150)

    # 五根直线
    DrawLine(-149, -9, -40, 5)
    DrawLine(-83, 52, -67, 20)
    DrawLine(2, 70, -97, 24)
    DrawLine(83, 42, -120, 15)
    DrawLine(145, -24, -155, 5)
def DrawEye():
    DrawDoubleDot(38, 0, 20)
def DrawMouth():
    DrawLine(-15, -30, 3, 30)
    t.seth(70)
    t.circle(18, -125)
def DrawCheek():
    t.pencolor("#f8bbd0")
    DrawDoubleDot(-45, -20, 23)
def Wait():
    t.ht()
    t.done()

def DrawHead():
    Init()
    DrawOutline()
    DrawHair()
    DrawEye()
    DrawMouth()
    DrawCheek()
    Wait()

DrawHead()