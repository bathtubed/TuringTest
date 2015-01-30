#include "Logger.h"

/********* STATIC LOGGER DATA MEMBERS *************/

shared_ptr<LogService> Logger::service = nullptr;
string Logger::path;

std::function<LogService *()> Logger::factory = []()
{
	return new FileLogger(Logger::GetFullPath()+LOG_STATE_OUT_FILE_NAME, Logger::GetMakeDirCommand());
};

/********** STATIC LOGGER CONSTANTS *****************/
/*
const char* SERVICE::text[] = {
		"GENERAL", "POWER", "SENSORS", "MOTORS", "PNEUMATICS"
};
*/

const char* LEVEL_t::text[] = {
		"EMER", "ALERT", "CRIT", "ERR", "WARN", "NOTICE", "INFO", "DEBUG"
};

const char* SUBSYSTEM::text[] = {
		"TEST"
};


/*
const int Logger::LogFrame()
{
	return GetInstance().LogAll();
}
*/


/******** STATIC LOGGER GET FUNCTIONS **********/

const string Logger::GetLogPath()
{
	return string(LOG_HOME);
}

const string Logger::GetRunTimeDirectory()
{
	/*auto t = time(0);
	auto tm = localtime(&t);
	char buf[32] = "";
	strftime(buf, 32, "%F_%X", tm);
	return string(buf);
	*/
	using std::ios_base;
	static string runTimeID;
	if(runTimeID.empty())
	{
		unsigned int nRunTimeID = 0;
		std::fstream rtFile(GetLogPath()+"runtimeID", ios_base::in);
		rtFile>>nRunTimeID;
		nRunTimeID++;

		rtFile.close();
		rtFile.open(GetLogPath()+"runtimeID", ios_base::out | ios_base::trunc);
		rtFile<<nRunTimeID;

		stringstream ss;
		ss.width(5);
		ss.fill('0');
		ss<<nRunTimeID;
		runTimeID = ss.str();
	}
	return runTimeID;
}

const string Logger::GetFullPath()
{
	if(path.empty())
	{
		path = GetLogPath()+GetRunTimeDirectory()+"/";
	}
	return path;
}

const string Logger::GetMakeDirCommand()
{
	return string("mkdir ") + GetFullPath();
}

const string Logger::MakeLogFileName(const string SUBS, const string COMP, const string TYPE)
{
	return GetFullPath()+SUBS+'.'+COMP+'.'+TYPE;
}

LogService &Logger::GetInstance()
{
	if(service == nullptr)
		service = shared_ptr<LogService>(factory());
	return *service;
}

// Takes in Service, level, and state of a part of a robot and stores it in 'data'
const int Logger::LogState(const char * const SERV, const int LEV, const char * text) {
	GetInstance().logText()<<"["<<SERV<<"]["<<LEVEL_t::text[LEV]<<"] "<<text<<std::endl;
#ifndef DEBUG_MODE
	if(LEV != LEVEL_t::INFO)
#endif
		GetInstance().logStdout()<<"["<<SERV<<"] "<<text<<std::endl;
	return 0;
}

