class Mainform : public Form
{
    TextBox* txtFilePath;
    TextBox* txtFileNumber;

    ProgressBar* progressBar;

public:
    void Button1_Click() {

        String filePath = txtFilePath->getText();
        int number = atoi(txtFileNumber->getText().c_str());

        FileSplitter splitter(filePath, number, progressBar);

        splitter.split();

    }
};