#include<iostream>
#include<cstdlib>
#include<filesystem>
#include<string>
#include<fstream>
using namespace std;

int main(){
	bool isWin;
	#ifdef _WIN32
		isWin=true;
	#else
		isWin=false;
	#endif
	bool install=true;
	string ask;
	bool sysIsCopied;
	string pathToIlyaOS;
	string pathToCopy;
	while (install){
		cout<<"вас приветствует установщик ilyaOS 2.5!"<<endl;
		cout<<std::filesystem::current_path().string()<<"/"<<endl<<"это путь к файлам IlyaOS? (y/n) ";
		getline(cin, ask);
		if (ask=="n"){
			cout<<"укажите, где находится ilyaOS (полный путь, вместе с папкой)"<<endl;
			getline(cin, pathToIlyaOS);
		}
		else{
			
			pathToIlyaOS=std::filesystem::current_path().string()+"/";
		}
		cout<<"хотите ли вы копировать ilyaOS в другую папку?"<<endl;
		cout<<"желательно на данный момент в ручную копировать и запускать установщик там."<<endl;
		cout<<"(y/n) ";
		getline(cin, ask);
		if (ask=="y"){
			sysIsCopied=1;
			cout<<"укажите куда вы хотите копировать ilyaOS (полный путь)"<<endl;
			getline(cin, pathToCopy);
			pathToCopy=string(pathToCopy)+"/";
			try{
				#ifdef _WIN32
					cout<<"копирование..."<<endl;
					string commander="xcopy"+pathToIlyaOS+" "+pathToCopy+"/E /I";
					system(commander.c_str());
				#else
					cout<<"копирование..."<<endl;
					string commander="cp -r "+pathToIlyaOS+" "+pathToCopy;
					system(commander.c_str());
				#endif
			}
			catch (const char* error){
				cerr<<error<<endl;
				continue;
			}
			
		}
		else{
			sysIsCopied=0;
		}
		cout<<"осталось совсем чуть-чуть."<<endl;
		cout<<"введите имя будущего пользователя: ";
		string username;
		getline(cin, username);

		if (sysIsCopied){
			string toUserFile=pathToCopy+"ilyaOS/system/username";
			ofstream userfile(toUserFile);
			if (userfile.is_open()){
				userfile<<username;
				userfile.close();
			}
			else{
				cout<<"\033[31mE: \033[0mошибка в открытии файла"<<endl;
			}
		}
		if (!sysIsCopied){
			string toUserFile=pathToIlyaOS+"ilyaOS/system/username";
			ofstream userfile(toUserFile);
			if (userfile.is_open()){
				userfile<<username;
				userfile.close();
			}
			else{
				cout<<"\033[31mE: \033[0mошибка в открытии файла"<<endl;
			}
		}
		cout<<"установка завершена."<<endl;
		break;
	}
	return 0;
}