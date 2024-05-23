#ifndef SENECA_FILE_H_
#define SENECA_FILE_H_
namespace seneca {
   bool openFile(const char filename[]);
   void closeFile();
   int noOfRecords();
   bool read(char *name);
   bool read(int &empNumber);
   bool read(double &salary);
}
#endif // !SENECA_FILE_H_