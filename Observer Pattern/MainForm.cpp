class Mainform : public Form
{
    TextBox* txtFilePath;
    TextBox* txtFileNumber;

public:
    void Button1_Click() {

        String filePath = txtFilePath->getText();
        int number = atoi(txtFileNumber->getText().c_str());

        FileSplitter splitter(filePath, number);

        splitter.split();

    }
};