#include "stdafx.h"
#include <string.h>
#include <malloc.h>
#include <windows.h>


// exe->filebuffer  返回值为计算所得文件大小
int ReadPEFile(char* file_path, PVOID* pFileBuffer)
{
	FILE* pfile = NULL;  // 文件指针
	DWORD file_size = 0;   //存储计算出的文件大小
	LPVOID pTempFilebuffer = NULL;

	// 打开文件
    fopen_s(&pfile, file_path, "rb");  // 如果有新的指针，就要进行判断
	if (!pfile)
	{
		printf("打开exe文件失败！\n");//如果分配失败就要关闭文件、释放动态内存、指针指向NULL
		return 0;
	}
	// 读取文件大小
	fseek(pfile, 0, SEEK_END);
	file_size = ftell(pfile);
	fseek(pfile, 0, SEEK_SET);
	// 分配空间
	pTempFilebuffer = malloc(file_size);  // 如果有新的指针，就要进行判断
	if (!pTempFilebuffer)
	{
		printf("分配空间失败！\n");//如果分配失败就要关闭文件、释放动态内存、指针指向NULL
		fclose(pfile);
		return 0;
	}
	// 将数据读取到内存中
	size_t n = fread(pTempFilebuffer, file_size, 1, pfile);
	if (!n)
	{
		printf("数据读取到内存中失败！\n"); //如果分配失败就要关闭文件、释放动态内存、指针指向NULL
		fclose(pfile);
		free(pTempFilebuffer);
		return 0;
	}
	// 关闭文件(已经读取到内存了)
	*pFileBuffer = pTempFilebuffer;
	pTempFilebuffer = NULL;   //指针指向NULL
	fclose(pfile);
	return file_size;
}

// filebuffer -> imagebuffer
DWORD CopyFileBufferToImageBuffer(PVOID pFileBuffer, PVOID* pImageBuffer)
{
	// 初始化PE头部结构体
	PIMAGE_DOS_HEADER pDosHeader = NULL;
	PIMAGE_NT_HEADERS pNTHeader = NULL;
	PIMAGE_FILE_HEADER pPEHeader = NULL;
	PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
	PIMAGE_SECTION_HEADER pSectionHeader = NULL;
	// 初始化IMAGE_BUFFER指针(temparay)
	LPVOID pTempImagebuffer = NULL;

	if (!pFileBuffer)
	{
		printf("(2pimagebuffer阶段)读取到内存的pfilebuffer无效！\n");
		return 0;
	}
	// 判断是否是可执行文件
	if (*((PWORD)pFileBuffer) != IMAGE_DOS_SIGNATURE)  // IMAGE_DOS_SIGNATURE是4字节，将pFileBuffer强制类型转换为4字节指针类型（PWORD）
	{
		printf("(2pimagebuffer阶段)不含MZ标志，不是exe文件！\n");
		return 0;
	}
	//强制结构体类型转换pDosHeader
	pDosHeader = PIMAGE_DOS_HEADER(pFileBuffer);
	//判断是否含有PE标志       
	if (*((PDWORD)((DWORD)pFileBuffer + pDosHeader->e_lfanew)) != IMAGE_NT_SIGNATURE) // 注意指针的加法是：去掉一个*后的类型相加。必须转换为DWORD类型再加减。
	{																			  //相加后的和 强制类型转换为4字节指针类型（PWORD） IMAGE_NT_SIGNATURE 4BYTES
		printf("(2pimagebuffer阶段)不是有效的PE标志！\n");
		return 0;
	}
	// 强制结构体类型转换  利用强制类型转换构造区块
	pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pFileBuffer + pDosHeader->e_lfanew);
	pPEHeader = (PIMAGE_FILE_HEADER)((DWORD)pNTHeader + 4);
	pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader + IMAGE_SIZEOF_FILE_HEADER);
	pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pOptionHeader + pPEHeader->SizeOfOptionalHeader);

	// 分配动态内存，SizeOfImage表示装进内存总大小
	pTempImagebuffer = malloc(pOptionHeader->SizeOfImage);
	if (!pTempImagebuffer)
	{
		printf("分配动态内存失败！\n");
		free(pTempImagebuffer);
		return 0;
	}
	// 初始化动态内存
	memset(pTempImagebuffer, 0, pOptionHeader->SizeOfImage);
	// 拷贝头部
	memcpy(pTempImagebuffer, pDosHeader, pOptionHeader->SizeOfHeaders);
	// 循环拷贝节表，注意对齐
	PIMAGE_SECTION_HEADER pTempSectionHeader = pSectionHeader;
	for (DWORD i = 0; i<pPEHeader->NumberOfSections; i++, pTempSectionHeader++)
	{
		memcpy((void*)((DWORD)pTempImagebuffer + pTempSectionHeader->VirtualAddress), (void*)((DWORD)pFileBuffer + pTempSectionHeader->PointerToRawData), pTempSectionHeader->SizeOfRawData);
	}
	// 返回数据
	*pImageBuffer = pTempImagebuffer;
	pTempImagebuffer = NULL;    //指针指向NULL
	return pOptionHeader->SizeOfImage;
}

//imagebuffer->newbuffer
DWORD CopyImageBufferToNewBuffer(PVOID pImageBuffer, PVOID* pNewBuffer)
{
	// 初始化PE头部结构体
	PIMAGE_DOS_HEADER pDosHeader = NULL;
	PIMAGE_NT_HEADERS pNTHeader = NULL;
	PIMAGE_FILE_HEADER pPEHeader = NULL;
	PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
	PIMAGE_SECTION_HEADER pSectionHeader = NULL;

	// 初始化NEW_BUFFER指针(temparay)
	LPVOID pTempNewbuffer = NULL;

	// 判断pImageBuffer是否有效
	if (!pImageBuffer)
	{
		printf("(2pnewbuffer阶段)读取到内存的pimagebuffer无效！\n");
		return 0;
	}
	//判断是不是exe文件
	if (*((PWORD)pImageBuffer) != IMAGE_DOS_SIGNATURE)
	{
		printf("(2pnewbuffer阶段)不含MZ标志，不是exe文件！\n");
		return 0;
	}
	// 强制结构体类型转换
	pDosHeader = (PIMAGE_DOS_HEADER)pImageBuffer;
	if (*((PDWORD)((DWORD)pImageBuffer + pDosHeader->e_lfanew)) != IMAGE_NT_SIGNATURE)
	{
		printf("(2pnewbuffer阶段)不是有效的PE标志！\n");
		return 0;
	}
	// 强制结构体类型转换
	pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pImageBuffer + pDosHeader->e_lfanew);
	pPEHeader = (PIMAGE_FILE_HEADER)((DWORD)pNTHeader + 4); // 这里必须强制类型转换
	pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader + IMAGE_SIZEOF_FILE_HEADER);
	pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pOptionHeader + pPEHeader->SizeOfOptionalHeader);

	//获取new_buf	fer的大小
	int new_buffer_size = pOptionHeader->SizeOfHeaders;
	for (DWORD i = 0; i<pPEHeader->NumberOfSections; i++)
	{
		new_buffer_size += pSectionHeader[i].SizeOfRawData;  // pSectionHeader[i]另一种加法
	}
	// 分配内存（newbuffer）
	pTempNewbuffer = malloc(new_buffer_size);
	if (!pTempNewbuffer)
	{
		printf("(2pnewbuffer阶段)分配Newbuffer失败！\n");
		return 0;
	}
	memset(pTempNewbuffer, 0, new_buffer_size);
	// 拷贝头部
	memcpy(pTempNewbuffer, pDosHeader, pOptionHeader->SizeOfHeaders);
	// 循环拷贝节区
	PIMAGE_SECTION_HEADER pTempSectionHeader = pSectionHeader;
	for (DWORD j = 0; j<pPEHeader->NumberOfSections; j++, pTempSectionHeader++)
	{	//PointerToRawData节区在文件中的偏移,VirtualAddress节区在内存中的偏移地址,SizeOfRawData节在文件中对齐后的尺寸
		memcpy((PDWORD)((DWORD)pTempNewbuffer + pTempSectionHeader->PointerToRawData), (PDWORD)((DWORD)pImageBuffer + pTempSectionHeader->VirtualAddress), pTempSectionHeader->SizeOfRawData);
	}
	//返回数据
	*pNewBuffer = pTempNewbuffer; //暂存的数据传给参数后释放
	pTempNewbuffer = NULL;
	return new_buffer_size;  // 返回计算得到的分配内存的大小
}

//newbuffer->存盘
int newbuffer_write2_exe(PVOID NewFileBuffer, DWORD FileSize, char* FilePath)
{
	FILE* fpl;
	fopen_s(&fpl, FilePath, "wb");
	if (fpl != NULL)
	{
		fwrite(NewFileBuffer, FileSize, 1, fpl);
	}
	fclose(fpl);
	return 1;
}

DWORD MoveExportTable(PVOID pFileBuffer, DWORD FileBuffer, PVOID* pFileBuffer_ExportTable)
{

}

void operate_pe()
{   // 初始化操作
	PVOID pFileBuffer = NULL;
	PVOID pImageBuffer = NULL;
	PVOID pNewFileBuffer = NULL;
	DWORD NewFileBufferSize = 0;
	//char file_path[] = "D:\\Lib\\IPMSG2007.exe";
	char file_path[] = "C:\\Windows\\System32\\notepad.exe";
	char write_file_path[] = "D:\\Lib\\cp_notepad.exe";

	// exe->filebuffer
	int ret1 = ReadPEFile(file_path, &pFileBuffer);  // &pFileBuffer(void**类型) 传递地址对其值可以进行修改
	printf("exe->filebuffer  返回值为计算所得文件大小：%#x\n", ret1);
	// filebuffer -> imagebuffer
	int ret2 = CopyFileBufferToImageBuffer(pFileBuffer, &pImageBuffer);
	printf("filebuffer -> imagebuffer返回值为计算所得文件大小：%#x\n", ret2);
	//imagebuffer->newbuffer
	int FileSize = CopyImageBufferToNewBuffer(pImageBuffer, &pNewFileBuffer);
	printf("imagebuffer->newbuffer返回值为计算所得文件大小：%#x\n", FileSize);
	//newbuffer->存盘
	int ret4 = newbuffer_write2_exe(pNewFileBuffer, FileSize, write_file_path);
	printf("newbuffer->存盘返回值为：%d\n", ret4);
}


int main()
{
	operate_pe();
	getchar();
	return 0;
}
