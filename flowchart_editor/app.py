#!/usr/bin/python

from Tkinter import *
import tkMessageBox
import tkFileDialog as filedialog
import math
# this file demonstrates the movement of a single canvas item under mouse control


class popupWindow(object):
    def __init__(self,master):
        top=self.top=Toplevel(master)
        self.l=Label(top,text="Enter your text!")
        self.l.pack()
        self.e=Entry(top)
        self.e.pack()
        self.b=Button(top,text='OK',command=self.cleanup)
        self.b.pack()

    def cleanup(self):
        self.value=self.e.get()
        self.top.destroy()

class Test(Frame):	
#######################EVENT HANDLING##########################

    def mouseDown(self, event):
        # remember where the mouse went down
        self.lastx = event.x
        self.lasty = event.y
	if self.mod:	
		self.draw.delete(CURRENT)


    def mouseMove(self, event):
        # whatever the mouse is over gets tagged as CURRENT for free by tk.
        self.draw.move(CURRENT, event.x - self.lastx, event.y - self.lasty)
        self.lastx = event.x
        self.lasty = event.y


    def mouseEnter(self, event):
        # the CURRENT tag is applied to the object the cursor is over.
        # this happens automatically.
        self.draw.itemconfig(CURRENT, fill="red")

    def mouseLeave(self, event):
        # the CURRENT tag is applied to the object the cursor is over.
        # this happens automatically.
        self.draw.itemconfig(CURRENT, fill="green")


##########################Drawing UI###########################


    def createWidgets(self):
	Menuframe = Frame(self)
	self.createMenubar(Menuframe)
	Menuframe.pack(side=TOP)
	frame1 = Frame(self)
	self.createToolbar(frame1)
	frame1.pack(side=TOP,fill=BOTH)
	frame2 = Frame(self)
	self.createWorkspace(frame2)
	frame2.pack(side=TOP,fill=BOTH);


    def createMenubar(self,f):
	self.mBtn1 = Button(f, text='New', foreground='red',
                           command=self.new)
	self.mBtn2 = Button(f, text='Open', foreground='red',
                           command=self.Open)
	self.mBtn3 = Button(f, text='Save', foreground='red',
                           command=self.save)
	self.mBtn4 = Button(f, text='Close', foreground='red',
                           command=self.close)
      	self.mBtn1.pack(side=LEFT) 
	self.mBtn2.pack(side=LEFT)
	self.mBtn3.pack(side=LEFT)
	self.mBtn4.pack(side=LEFT)

    def createToolbar(self,f):
	self.Btn1 = Button(f, text='OVAL', foreground='red',
                           command=self.createOval)
	self.Btn2 = Button(f, text='RIGHT ARROW', foreground='red',
                           command=self.createRightarrow)
	self.Btn3 = Button(f, text='LEFT ARROW', foreground='red',
                           command=self.createLeftarrow)
	self.Btn4 = Button(f, text='DOWN ARROW', foreground='red',
                           command=self.createDownarrow)
	self.Btn5 = Button(f, text='UP ARROW', foreground='red',
                           command=self.createUparrow)
	self.Btn6 = Button(f, text='RECTANGLE', foreground='red',
                           command=self.createRectangle)
	self.Btn7 = Button(f, text='DIAMOND', fg='red',
			   command=self.createRotrectangle)
	self.Btn8 = Button(f, text='TEXT', fg='red',
			   command=self.createText)	
	self.Btn9 = Button(f, text='DeleteOFF', fg='red',
			   command=self.deleteSelection)
	
	self.Btn1.pack(side=RIGHT)
	self.Btn2.pack(side=RIGHT)
	self.Btn3.pack(side=RIGHT)
	self.Btn4.pack(side=RIGHT)
  	self.Btn5.pack(side=RIGHT)
	self.Btn6.pack(side=RIGHT)
	self.Btn7.pack(side=RIGHT) 
	self.Btn8.pack(side=RIGHT)
	self.Btn9.pack(side=RIGHT)

    def createWorkspace(self,f):	
        self.draw = Canvas(f, width="10i", height="5i")
        self.draw.pack(side=LEFT)

        Widget.bind(self.draw, "<1>", self.mouseDown)
        Widget.bind(self.draw, "<B1-Motion>", self.mouseMove)


    def createText(self):
	self.w=popupWindow(self.master)
        self.master.wait_window(self.w.top)
	
	res = self.draw.create_text(10,10,anchor="nw")
	self.draw.itemconfig(res,text=self.w.value)	
	self.registertag(res)
	self.objtype += ["Text"]
	self.txtval += self.w.value +'|'
	self.objcnt = self.objcnt+1



    def createRotrectangle(self):
	res = self.draw.create_polygon((0,25),(25,50),(50,25),(25,0),fill="green",tags="selected")
	
	self.registertag(res)
	self.objtype += ["Diamond"]
	self.objcnt = self.objcnt+1


    def createOval(self):
	res = self.draw.create_oval(0,0,40,40,fill="green",tags="selected")
	self.registertag(res)
	self.objtype += ["Oval"]
	self.objcnt = self.objcnt+1

    def createRectangle(self):
	res = self.draw.create_rectangle(0,0,40,40,fill="green",tags="selected")
	self.registertag(res)
	self.objtype += ["Rectangle"]
	self.objcnt = self.objcnt+1

    def createRightarrow(self):
	res = self.draw.create_line(0,20,40,20,arrow="last",tags="selected")
	self.registertag(res)
	self.objtype +=["RArrow"]
	self.objcnt = self.objcnt+1

    def createLeftarrow(self):
	res = self.draw.create_line(0,20,40,20,arrow="first",tags="selected")
	self.registertag(res)
	self.objtype += ["LArrow"]
	self.objcnt = self.objcnt+1

    def createUparrow(self):
	res = self.draw.create_line(20,0,20,40,arrow="first",tags="selected")
	self.registertag(res)
	self.objtype += ["UArrow"]
	self.objcnt = self.objcnt+1

    def createDownarrow(self):
	res = self.draw.create_line(20,0,20,40,arrow="last",tags="selected")
	self.registertag(res)
	self.objtype += ["DArrow"]
	self.objcnt = self.objcnt+1



    def deleteSelection(self):
	if self.mod:
    		self.Btn9.configure(text='DeleteOFF',bg="white")
	else:
		self.Btn9.configure(text='DeleteON',bg="green")
	self.mod=1-self.mod
	self.objcnt = self.objcnt-1

    def registertag(self,tag):
	self.objarr += [tag]
        self.draw.tag_bind(tag, "<Any-Enter>", self.mouseEnter)
        self.draw.tag_bind(tag, "<Any-Leave>", self.mouseLeave)

#######################FILE OPERATIONS############################
	
    def new(self):
 	op_path = filedialog.askopenfilename()
	opfile = open(op_path,'a')
	opfile.close()


    def Open(self):
	for i in self.objarr:
		self.draw.delete(i)
	file_path = filedialog.askopenfilename()
	thefile = open(file_path,'r')
	mytype = thefile.readline().split('|')
	mycoords = thefile.readline().split('|')
	self.txtval = thefile.readline()
	self.txtvalarr = self.txtval.split('|')
	self.txtvalidx=0

	self.objtype=mytype
	temp=mytype[len(mytype)-1]	
	mytype[len(mytype)-1] = temp[:len(temp)-1]
	print mytype
	print mycoords
	self.objcnt=0;
	self.objarr=[]
	for i in range(0,len(mytype)):
		temp=mycoords[i].split(' ')
		if len(temp) >=2  :
			self.objcnt +=1	
			x0=float(temp[0])
			y0=float(temp[1])
			if len(temp) > 2:	
				x1=float(temp[2])
				y1=float(temp[3])

			if mytype[i] == "Oval":
				res = self.draw.create_oval(x0,y0,x1,y1,fill="green",tags="selected")			
				self.registertag(res)
			elif mytype[i] == "Rectangle":
				res = self.draw.create_rectangle(x0,y0,x1,y1,fill="green",tags="selected")
				self.registertag(res)

			elif mytype[i] == "UArrow":
				res = self.draw.create_line(x0,y0,x1,y1,arrow="first",tags="selected")
				self.registertag(res)
			elif mytype[i] == "DArrow":
				res = self.draw.create_line(x0,y0,x1,y1,arrow="last",tags="selected")
				self.registertag(res)
			elif mytype[i] == "LArrow":
				res = self.draw.create_line(x0,y0,x1,y1,arrow="first",tags="selected")
				self.registertag(res)

			elif mytype[i] == "RArrow":
				res = self.draw.create_line(x0,y0,x1,y1,arrow="last",tags="selected")
				self.registertag(res)


			elif mytype[i] == "Text":
				res = self.draw.create_text(temp[0],temp[1],anchor="nw")
				self.draw.itemconfig(res,text=self.txtvalarr[self.txtvalidx])
				self.txtvalidx = self.txtvalidx+1
				self.registertag(res)


			elif mytype[i] == "Diamond":
				res = self.draw.create_polygon((temp[0],temp[1]),(temp[2],temp[3]),(temp[4],temp[5]),(temp[6],temp[7]),fill="green",tags="selected")			
				self.registertag(res)

    def save(self):
	self.objcoords=""
	self.rescoords=[]
	thefile = filedialog.asksaveasfile(mode='w',defaultextension=".txt")
	
	for i in self.objarr:
		temp=""
		self.rescoords=self.draw.coords(i)
		print self.draw.coords(i)
		for j in range(0,len(self.rescoords)):
			print j
			temp += "{:.1f}".format(self.rescoords[j])+' '
		temp=temp[:len(temp)-1]
		self.objcoords += temp+'|'
	mytype = "|".join(self.objtype)
	mytype+='\n'
	thefile.write(mytype)
	thefile.write(self.objcoords + '\n')
	thefile.write(self.txtval)
	thefile.close()	

    def close(self):
	result = tkMessageBox.askquestion("Close", "Do you want to save your work?", icon='warning')
	if result == 'yes':
        	self.save()
	else:
		for i in self.objarr:
			self.draw.delete(i)

    def __init__(self, master=None):
        Frame.__init__(self, master)
        Pack.config(self)
        self.current=[CURRENT,CURRENT]
	self.mod=0
	self.createWidgets()
	self.objarr = []
	self.objtype = []
	self.objcnt = 0
	self.txtval = ""

def main():
	global root
	root = Tk()
	Test(root)
	root.title('Abhinav UI v '+'0.0')
	root.mainloop()


main()
