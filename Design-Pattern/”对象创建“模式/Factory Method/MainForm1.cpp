class MainForm : public Form
{
	TextBox* txtFilePath;
	TextBox* txtFileNumber;
	ProgressBar* progressBar;

public:
	void Button1_Click() {



		ISplitter* splitter =
			new BinarySplitter();//ÒÀÀµ¾ßÌåÀà

		splitter->split();

	}
};