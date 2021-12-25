import turtle as t

# setup(width=_CFG['width'], height=_CFG['height'], startx=_CFG['leftright'], starty=_CFG['topbottom'])
# Screen 专有方法,设置主窗口的大小和位置
t.setup(600, 400)

# penup 画笔控制-画笔抬起
# 移动时不画线
# 等价函数 penup() | pu() | up()
t.penup()

# goto(x, y=None)
# 动作-移动和绘制-移动到一个绝对坐标。
# 如果画笔已落下将会画线。
# 不改变海龟的朝向。
# 等价函数 goto() | setpos() | setposition()
print("pos:", t.pos())  # 默认为 (0.00,0.00)，屏幕中中心
t.goto(-180, -80)

# pendown 画笔控制-绘图状态-画笔落下exit
# 移动时将画线
# 等价函数 pendown() | pd() | down()
t.pendown()

# pensize 画笔控制-绘图状态-画笔粗细
# 设置线条的粗细为 width 或返回该值。
# 等价函数 pensize() | width()
t.pensize(5)

# pencolor 画笔控制-绘图状态-画笔颜色
# 返回或设置画笔颜色
t.pencolor("black")

# seth(to_angle) 动作-移动和绘制-设置朝向
# 设置海龟的朝向为 to_angle。
# 等价函数 setheading() | seth()
print("mode:", t.mode())  # 默认为 0
print("default heading:", t.heading())  # 默认为 0，朝右，代表东边


t.seth(-20)
print("-20 heading:", t.heading())  # 值为 340， 也为 -20，朝右下


# circle(radius, extent=None, steps=None) 动作-移动和绘制-画圆
# 绘制一个 radius 指定半径的圆。
# 圆心在海龟朝向的左边 radius 个单位（垂直方向左侧）；
# extent 为一个夹角，用来决定绘制圆的一部分。
# radius 为正值则朝逆时针方向绘制圆弧，否则朝顺时针方向。
# 最终海龟的朝向会依据 extent 的值而改变
t.circle(500, 40)
print("heading:", t.heading())  # 值为 20

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
print("pos1:", t.pos())

t.penup()
t.goto(-83, 52)
t.pendown()
t.seth(-67)
t.fd(20)
print("pos2:", t.pos())

t.penup()
t.goto(2, 70)
t.pendown()
t.seth(-97)
t.fd(24)
print("pos3:", t.pos())

t.penup()
t.goto(83, 42)
t.pendown()
t.seth(-120)
t.fd(15)
print("pos4:", t.pos())

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

# done 屏幕事件
# 必须作为一个海龟绘图程序的结束语句, 否则窗口闪一下就关闭了
# 等价函数 mainloop() | done()
t.done()
