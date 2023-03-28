class MainForm : public Form
{
	SplitterFactory* factory;

public:
	MainForm(SplitterFactory* factory) {
		this->factory = factory;
	}
	void Button1_Click() {



		ISplitter* splitter =
			factory->CreateSplitter();	//¶àÌ¬new

		splitter->split();

	}
};