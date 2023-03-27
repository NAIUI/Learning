class IProgress {
public:
	virtual void DoProgress(float value) = 0;
	virtual ~IProgress(){}
};

class FileSplitter
{
	string m_filePath;
	int m_fileNumber;

	//ProgressBar* m_progressBar;	//具体通知控件
	IProgress* m_iprogress;			//抽象通知机制

public:
	FileSplitter(const string& filePath, int fileNumber) :
		m_filePath(filePath),
		m_fileNumber(fileNumber),
		m_iprogress(iprogress) {

	}

	void split() {

		// 1.读取大文件

		// 2.分批次向小文件中写入
		for (int i = 0; i < m_fileNumber; ++i) {
			//...

			if (m_iprogress != null) {
				float progressValue = m_fileNumber;
				progressValue = (i + 1) / progressValue;
				m_iprogress->DoProgress(progressValue);	//更新进度条
			}
		}
	}
};