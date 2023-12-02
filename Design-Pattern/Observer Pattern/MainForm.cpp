class Mainform : public Form, public IProgress
{
    TextBox* txtFilePath;
    TextBox* txtFileNumber;

    ProgressBar* progressBar;

public:
    void Button1_Click() {

        String filePath = txtFilePath->getText();
        int number = atoi(txtFileNumber->getText().c_str());

        ConsoleNotifer cn;

        FileSplitter splitter(filePath, number);

        splitter.addIProgress(this);
        splitter.addIProgress(&cn);

        splitter.split();

    }

    virtual void DoProgress(float value) {
        progressBar->setValue(value);
    }
};

class ConsoleNotifer : public IProgress{
public:
    virtual void DoProgress(float value) {
        cout << ".";
    }
};