addressbook
-------------------
Example with hardcoded GUI-Design.


calculatorform
-------------------
This is the GUI-Designer single inheritance approach.
It keeps the generated code separated from the manually written source code through 
the ui object, something that helps making changes more controllable.

multipleinheritance
-------------------
This is the GUI-Designer multiple inheritance approach.

Slots can be auto connected. Lets say there is a button pushButton2. The definition of
the method 

	private slots:
	    void on_pushButton2_clicked();

auto connects the buttons clicked signal to this on_pushButton2_clicked slot.

single_pch
-------------------
This is a GUI-Designer single inheritance approach with pre compiled headers
support.