import turtle as t

t.setup(600, 400)
t.penup()
t.goto(-180, -80)
t.pendown()
t.pensize(5)
t.pencolor("black")
t.seth(-20)
t.circle(500, 40)
t.seth(110)
t.circle(182, 140)
t.seth(150)
for i in range(4):
    t.circle(-35, 143)
    t.circle(19, 110)

t.circle(-35, 135)
t.left(5)
t.circle(19, 100)
t.circle(-24.5, 150)

t.penup()
t.goto(-149, -9)
t.pendown()
t.seth(-40)
t.fd(5)

t.penup()
t.goto(-83, 52)
t.pendown()
t.seth(-67)
t.fd(20)

t.penup()
t.goto(2, 70)
t.pendown()
t.seth(-97)
t.fd(24)

t.penup()
t.goto(83, 42)
t.pendown()
t.seth(-120)
t.fd(15)

t.penup()
t.goto(145, -24)
t.pendown()
t.seth(-155)
t.fd(5)

t.penup()
t.goto(-38, 0)
t.pendown()
t.pencolor("black")
t.dot(20)


t.penup()
t.goto(38, 0)
t.pendown()
t.pencolor("black")
t.dot(20)

t.penup()
t.goto(-15, -30)
t.pendown()
t.seth(3)
t.fd(30)

t.seth(70)
t.circle(18, -125)


t.penup()
t.goto(-45, -20)
t.pendown()
t.pencolor("#f8bbd0")
t.dot(23)


t.penup()
t.goto(45, -20)
t.pendown()
t.pencolor("#f8bbd0")
t.dot(23)

t.penup()
t.ht()

t.done()
