#include "ilyaOS/system/libes.cxx"
#include<filesystem>
#include<fstream>
#include "ilyaOS/cmd/forSystem.cxx"

namespace fs = std::filesystem;

string settings, desktop, start;
string fileManager, createFile, removeFile;
bool on = true;
bool onSystem = false;

int main()
{
	ifstream file("ilyaOS/system/username");
	if (file.is_open()){
		getline(file, username);
		file.close();
	}
	else{
		cout<<"ошибка в открытии файла."<<endl;
	}
	cout<<"загрузка..."<<endl;
	while (on)
	{
		system("clear || cls");
		date();
		cout<<"выкл"<<endl;
		cout<<"добро пожаловать!"<<endl;
		cout<<"выберете пользователя которым будете пользоваться сегодня:"<<endl;
		cout<<username<<", root"<<endl;
		string inputChoose;
		getline(cin, inputChoose);
		if(inputChoose==username)
		{
			onSystem=true;
			usingUser=username;
		}
		else if(inputChoose=="выкл")
		{
			on = false;
		}
		else if(inputChoose==root)
		{
			onSystem=true;
			usingUser=root;
		}
		while (onSystem)
		{
			system("clear || cls");
			date();
			cout<<"пуск"<<endl;
			getline(cin, desktop);
			if(desktop=="пуск")
			{
				cout<<"настройки, выкл, изменить пользователя, проводник, терминал"<<endl;
				getline(cin, start);
				if(start=="выкл")
				{
					cout<<"выключение..."<<endl;
					on=false;
					break;
				}
				else if(start=="настройки")
				{
					while (true){
						cout<<usingUser<<endl;
						cout<<"версия системы, переименовать пользователя, выйти"<<endl;
						getline(cin, settings);
						if(settings=="выйти")
						{
							break;
						}
						else if(settings=="версия системы")
						{
							cout<<"2.5"<<endl;
						}
						else if(settings=="переименовать пользователя")
						{
							cout<<"введите новое имя пользователя: ";
							getline(cin, username);
						}
					}
				}
				else if(start=="изменить пользователя")
				{
					break;
				}
				else if(start=="терминал"){
					cout<<"просим вас быть аккуратными!"<<endl;
					cmd();
				}
				else if(start=="проводник"){
					while (true){
						system ("clear || cls");
						date();
						system("ls || dir");
						cout<<fs::current_path()<<endl;
						cout<<"выйти, создать, удалить, создать папку, удалить папку, выше, перейти в папку"<<endl;
						getline(cin, fileManager);
						if (fileManager=="выйти"){
							break;
						}
						else if(fileManager=="выше"){
							try{
								fs::current_path("..");
							}
							catch (std::filesystem::filesystem_error& e){
								cerr<<"\033[31m"<<e.what()<<"\033[0m"<<endl;
							}
						}
						else if(fileManager=="удалить папку"){
							string removeDir;
							cout<<"введите название папки: ";
							getline(cin, removeDir);
							#ifdef _WIN32
								string commander="del "+removeDir;
							#else
								string commander="rm -rf "+removeDir;
							#endif
							system(commander.c_str());
						}
						else if(fileManager=="создать папку"){
							string createDir;
							cout<<"введите название папки: ";
							getline(cin, createDir);
							if (createDir!=""){
								fs::create_directory(createDir);
							}
						}
						else if(fileManager=="создать"){
							cout<<"имя нового файла: "<<endl;
							getline(cin, createFile);
							#ifdef _WIN32
							string commander="type nul > "+createFile;
							#else
							string commander="touch "+createFile;
							#endif
							system(commander.c_str());
						}
						else if(fileManager=="удалить"){
							cout<<"введите удаляемый файл";
							getline(cin, removeFile);
							#ifdef _WIN32
							string commander="del "+removeFile;
							#else
							string commander="rm "+removeFile;
							#endif
							system(commander.c_str());
						}
					}
				}
			}
		}
	}
	return 0;
}
