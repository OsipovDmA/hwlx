#include <iostream>
#include <thread>
#include <map>
#include <vector>
#include <memory>
#include <chrono>
#include "nlohmann/json.hpp"

using namespace std;

struct dataStruct {
    int d1 = 0;
    int d2 = 0;
    int d3 = 0;
};

//================ControlBits================//

// dataStruct *_controlbits = nullptr;
// dataStruct _lastcontrolbits;

// //Разыменование и возвращение ссылки на структуру
// dataStruct& Bits() {
//     return *_controlbits;
// }

// dataStruct& ControlBitRW() {
// 	dataStruct* localcontrolbits;
// 	localcontrolbits = &Bits(); // В переменную localcontrolbits записывается адрес ссылки на структуру
// 	return *localcontrolbits; // Разыменование и возвращение ссылки на структуру   
// }

// int SendControlBits()
// {
// 	_lastcontrolbits = Bits();
// 	return 1;
// }

// dataStruct& ClearBit()
// {
// 	return _lastcontrolbits;
// }

// int UpdateControlBits()
// {
// 	*_controlbits = ClearBit();
// 	return 1;
// }

// int main() {

    
//     _controlbits = new dataStruct;
//     //Заполнение структуры в главном потоке
//     ControlBitRW().d1 = 1;
//     ControlBitRW().d2 = 0;
//     ControlBitRW().d3 = 1;
//     std::cout << "d1 = " << ControlBitRW().d1 << endl;
//     std::cout << "d2 = " << ControlBitRW().d2 << endl;
//     std::cout << "d3 = " << ControlBitRW().d3 << endl;
//     //Отправка в eth поток
//     SendControlBits();
// 	//Чтение струеутры в eth потоке
// 	auto controlbits = &ClearBit();
// 	int d1 = controlbits->d1;
// 	int d2 = controlbits->d2;
// 	int d3 = controlbits->d3;	
//     //Редактирование структуры в eth потоке
//     ClearBit().d1 = 0;
//     ClearBit().d2 = 1;
//     ClearBit().d3 = 0;
//     //Обновление структуры в главном потоке
//     UpdateControlBits();
//     //Чтение структуры в главном потоке
//     std::cout << "d1 = " << ControlBitRW().d1 << endl;
//     std::cout << "d2 = " << ControlBitRW().d2 << endl;
//     std::cout << "d3 = " << ControlBitRW().d3 << endl;

// }
//================ControlBits================//


//=================Telemetry=================//

// dataStruct* _telemetry = nullptr;
// dataStruct _lasttelemetry;
// dataStruct _currenttelemetry;

// dataStruct& Telemetry()
// {
// 	return *_telemetry;
// }

// int UpdateTelemetry()
// {
// 	_lasttelemetry = Telemetry();
// 	return 1;
// }

// int UploadTelemetry()
// {
// 	Telemetry() = _currenttelemetry;
// 	return 1;
// }

// dataStruct& TelemetryRW()
// {
// 	return _currenttelemetry;
// }

// void ModifyTelemetry()
// {
// 	auto telemetry = &TelemetryRW();

// 	telemetry->d1 = 1;
// 	telemetry->d2 = 1;
// 	telemetry->d3 = 1;

// }

// const dataStruct& TelemetryRO()
// {
// 	return _lasttelemetry;
// }
// int main () {
//     _telemetry = new dataStruct;

// 	//Перенос телеметрии из потока EtherCAT в главный поток
// 	UpdateTelemetry();
// 	//Считывание телеметрии в главном потоке
// 	auto telemetry = &TelemetryRO();
// 	int d1 = telemetry->d1;
// 	int d2 = telemetry->d2;
// 	int d3 = telemetry->d3;
//     std::cout << "d1 = " << d1 << endl;
//     std::cout << "d2 = " << d2 << endl;
//     std::cout << "d3 = " << d3 << endl;	

// 	//Считывние данных пришедших по сети
// 	ModifyTelemetry();

// 	//Считывание телеметрии в потоке EtherCAT
// 	UploadTelemetry();

// 	//Перенос телеметрии из потока EtherCAT в главный поток
// 	UpdateTelemetry();
// 	//Считывание телеметрии в главном потоке	
// 	telemetry = &TelemetryRO();
// 	d1 = telemetry->d1;
// 	d2 = telemetry->d2;
// 	d3 = telemetry->d3;
//     std::cout << "d1 = " << d1 << endl;
//     std::cout << "d2 = " << d2 << endl;
//     std::cout << "d3 = " << d3 << endl;

// }

//=================Telemetry=================//


//===================Tasks===================//

// enum ETHERCAT_TASK_STATE_t
// {
// 	ESTATE_READY = 1,
// 	ESTATE_BUSY = 2,
// 	ESTATE_COMPLETE = 3,
// 	ESTATE_ERROR = 4
// };

// enum ETHERCAT_TASK_CODE_t
// {
// 	// All possible tasks list
// 	ETASK_DEFAULT = 0x0001,
// 	ETASK_STANDBY = 0x0002,

// 	// XRay tasks
// 	ETASK_ENABLE_XRAY_DRIVE = 0x0200,
// 	ETASK_DISABLE_XRAY_DRIVE = 0x0201,
// 	ETASK_MOVE_XRAY = 0x0202,
// 	ETASK_STOP_XRAY = 0x0203,

// 	// kV detector tasks
// 	ETASK_ENABLE_KV_DETECTOR_DRIVE = 0x0300,
// 	ETASK_DISABLE_KV_DETECTOR_DRIVE = 0x0301,
// 	ETASK_MOVE_KV_DETECTOR = 0x0302,
// 	ETASK_STOP_KV_DETECTOR = 0x0303,

// 		// kV detector tasks
// 	ETASK_ENABLE_GANTRY_DRIVE = 0x0400,
// 	ETASK_DISABLE_GANTRY_DRIVE = 0x0401,
// 	ETASK_MOVE_GANTRY = 0x0402,
// 	ETASK_STOP_GANTRY = 0x0403,

// 	// For other drives

// 	ETASK_ENABLE_DRIVE = 0x0A00,
// 	ETASK_DISABLE_DRIVE = 0x0A01,
// 	ETASK_MOVE = 0x0A02,
// };


// class EthercatTaskManager
// {
// public:
// 	EthercatTaskManager() {

//     };
// 	EthercatTaskManager(const EthercatTaskManager& other) {
//         *this = other;        
//     };
// 	~EthercatTaskManager() {

//     };
// private:
// 	struct EthercatTask
// 	{
// 		std::string 			subsystem;
// 		ETHERCAT_TASK_CODE_t	code;
// 		uint64_t				ID;
// 		std::string				description;
// 		uint16_t 				position;
// 	};

// 	std::vector<std::shared_ptr<EthercatTask>> _vectorTasks;
// 	std::map<std::string, std::shared_ptr<EthercatTask>> _mapTasks;

// public:
// 	EthercatTaskManager& operator = (const EthercatTaskManager& other) {
//         this->Clear();
//         for(int taskNo = 0; taskNo < other._vectorTasks.size(); taskNo++)
//         {
//             std::shared_ptr<EthercatTask> ptrTask = std::shared_ptr<EthercatTask> ( new EthercatTask() );
//             *ptrTask = *other._vectorTasks[taskNo];
//             this->_vectorTasks.push_back(ptrTask);
//             this->_mapTasks.emplace(ptrTask->subsystem, ptrTask);
//         }
//         return *this;        
//     };
// 	void Add(std::string taskSubsystem, ETHERCAT_TASK_CODE_t taskCode, uint64_t taskID, std::string taskDescription) {
//         EthercatTask localTask;

//         localTask.subsystem = taskSubsystem;
//         localTask.code = taskCode;
//         localTask.ID = taskID;
//         localTask.description = taskDescription;
//         localTask.position = _vectorTasks.size();

//         std::shared_ptr<EthercatTask> ptrTask = std::shared_ptr<EthercatTask> ( new EthercatTask() );
//         *ptrTask = localTask;

//         auto mapIt = _mapTasks.find(ptrTask->subsystem); //метод find принимает ключ в качестве аргумента. Возвращает итератор к элементу, если он найден. Если элемент не найден, то возвращает итератор к концу map.
//         if(mapIt == _mapTasks.end())
//         {
//             // такого элемента еще нет
//             _vectorTasks.push_back(ptrTask); //в вектор добавляется новый элемент
//             _mapTasks.emplace(ptrTask->subsystem, ptrTask); //в map добавляется новый элемент
//         }
//         else
//         {
//             // такой элемент уже есть
//             uint16_t vecSwapIndex = mapIt->second->position; 
//             auto vectorSwapIt = _vectorTasks.begin() + vecSwapIndex;

//             // vector
//             _vectorTasks.erase(vectorSwapIt); //с помощью метода erase удаляется элемент с индексом vectorSwapIt
//             _vectorTasks.insert(vectorSwapIt, ptrTask); //с помощью метода insert в вектор добавляется элемент ptrTask по индексу vectorSwapIt
//             _vectorTasks.at(vecSwapIndex)->position	= vecSwapIndex; //метод at возвращает элемент под индексом vecSwapIndex
//             // map
//             _mapTasks.erase(ptrTask->subsystem); //с помощью метода erase удаляется элемент с ключем ptrTask->subsystem
//             _mapTasks.emplace(ptrTask->subsystem, ptrTask); //в map добавляется новый элемент
//         }        
//     };
// 	void Add(std::string taskSubsystem, ETHERCAT_TASK_CODE_t taskCode) {
//     	return Add(taskSubsystem, taskCode, 0, "");    
//     };
// 	void Clear() {
//         _vectorTasks.clear();
//         _mapTasks.clear();        
//     };
// 	size_t TaskPackSize() {
// 	    return _vectorTasks.size();        
//     };
// 	const EthercatTaskManager::EthercatTask& GetTask(uint16_t taskIndex) {
//     	return *_vectorTasks.at(taskIndex);    
//     };
// 	const EthercatTaskManager::EthercatTask& GetTask(std::string taskSubsystemName) {
//         if (_mapTasks.find(taskSubsystemName) != _mapTasks.end())
//         {
//             return *_mapTasks.find(taskSubsystemName)->second;
//         }
//         else
//         {
//             #if ETHERCATTASKMANAGER_LOGS
//             std::cout << __PRETTY_FUNCTION__ << ": error. slave <" + taskSubsystemName + "> has no active task or does not exist.\n";
//             #endif
//             std::shared_ptr<EthercatTask> _faultCausingTask = nullptr;
//             return *_faultCausingTask;
//         }        
//     };	
// };

// EthercatTaskManager* _taskManager = nullptr;
// std::shared_ptr<EthercatTaskManager> _currenttasks;
// bool _isProcessFunctionAvailable = false;


// EthercatTaskManager& Tasks() {
//     return *_taskManager;
// }

// EthercatTaskManager& Task() {
//     EthercatTaskManager* localTaskManager;
//     localTaskManager = &Tasks();
//     return *localTaskManager;
// } 

// int TryToReceiveTasksAndParameters() {
//     if(_isProcessFunctionAvailable) {
//         _isProcessFunctionAvailable = false;
//         *_currenttasks = Tasks();
//         Tasks().Clear(); 
//         return 1;
//     } else {
//         return 0;
//     }
// }

// void EnableReceivingTaskAndParameters() {
//     _isProcessFunctionAvailable = true;
// }

// int Process() {
//    EnableReceivingTaskAndParameters();
// }


// const EthercatTaskManager& CurrentTasks() {
//     return *_currenttasks;
// }

// void _GiveTasksToSlaves() {
//     if (TryToReceiveTasksAndParameters()) {
//         auto currentTasks = CurrentTasks();
//     }
// }



// int main() {
//     _taskManager = new EthercatTaskManager;

//     Task().Add("Gantry motion", ETASK_MOVE_GANTRY);

// } 

//===================Tasks===================//

#define SLAVE_NUM 2 

//////////////////////////////////////////////////////

struct DeviceInterface
{
	bool pp {false};
    bool hm {false};
    int command {0};
    int status {0};
    int p {0};
    int v {0};
    int a {0};
    int j {0};
};

struct DevicesStruct
{
    DeviceInterface &operator[](int index) {
        if (index == 1) {
            return debugDrive1;
        } else if (index == 2) {
            return debugDrive2;
        }
        
    }
	DeviceInterface debugDrive1;
	DeviceInterface debugDrive2;
};
//////////////////////////////////////////////////////


class Slave {

private:    
    int p {0};
    int v {0};
    int a {0};
    int j {0};
    int command {0};
    int status {0};
    //controlbits
    bool pp {false};
    bool hm {false};
    int ModeOfOperation {0};
    int StateDrive {0};
public:
    static int idStatic;
    int id {0};
    Slave() {
        idStatic++;
        id = idStatic;

    }
    int getP() {
        return p;
    }
    int getV() {
        return v;
    }
    int getA() {
        return a;
    }
    int getStatus() {
        return status;
    }
    void setP(int _p) {
        p = _p;
    }
    void setV(int _v) {
        v = _v;
    }
    void setA(int _a) {
        a = _a;
    }
    void setCommand(int _command) {
        command = _command;
    }
    void ControlDrive() {

        switch (StateDrive)
        {
        case 0:
            std::cout << "Drive disabled" << std::endl;
            status = 0;
            if (command == 1) StateDrive = 1;
            break;
        
        case 1:
            std::this_thread::sleep_for(1000ms);
            std::cout << "Drive enabled" << std::endl;
            status = 1;
            if (command == 0) StateDrive = 0;
            switch (ModeOfOperation)
            {
            case 0:
                break;
            case 1:
                std::cout << "PP mode" << std::endl;
                break;            
            case 2:
                std::cout << "HM mode" << std::endl;
                break;
            }
            break;
        }
        // if (hm == 1) {
        //     ModeOfOperation = 2;            
        // } else if (pp == 1) {
        //     ModeOfOperation = 1;
        // }
    }
};

class EthercatAPIData {
public:
    DevicesStruct _lastcontrolbits;

    static EthercatAPIData* _instance;
    DevicesStruct* _controlbits = nullptr;
public:
    static EthercatAPIData* Instance() {
        if (_instance == nullptr) {
            _instance = new EthercatAPIData;
            _instance->_controlbits = new DevicesStruct;
        }
        return _instance;
    }
    void Destroy()
    {
        delete _instance->_controlbits;

        delete _instance;
        
        _instance = nullptr;	
    }
    DevicesStruct& Bits()
    {
        return *_controlbits;
    } 

//////////////////////////////
    DevicesStruct& ClearBit()
    {
        return _lastcontrolbits;
    }

    const DevicesStruct& ControlBitsRO()
    {
        return _lastcontrolbits;
    } 
    
    int EnableReceivingControlBits()
    {
        // EthercatAPIData::Instance()->ContbitsMutex().lock();
        _lastcontrolbits = EthercatAPIData::Instance()->Bits();
        // EthercatAPIData::Instance()->
        // EthercatAPIData::Instance()->ContbitsMutex().unlock();
        return 1;
    }  
    int UpdateControlBits() {
        *_controlbits = ClearBit();
    }

};
EthercatAPIData* EthercatAPIData::_instance = nullptr;

class MainOperator {
public:
    int i {0};
    int cycleState {0};
    std::vector<shared_ptr<Slave>> _vectorSlaves;
    MainOperator() {
        for (int i = 0; i < SLAVE_NUM; i++) {
            _vectorSlaves.push_back(shared_ptr<Slave>(new Slave));
        }
    }
    void Cycle() {      
             
        switch (cycleState)
        {
        case 0: //init
            // for ()
            cycleState = 1;
            break;
        case 1:
            i++;
            if (i == 100000000) {
                i = 0;
                cycleState = 2;
            }
            break;
        
        case 2:
            // std::cout << "HI from cycle" << std::endl;
            auto contbits = EthercatAPIData::Instance()->ClearBit();
            // *contbits.debugDrive1.status = 1;
            // EthercatAPIData::Instance()->ClearBit().debugDrive1.a = 22;
            // EthercatAPIData::Instance()->UpdateControlBits();
            // std::cout << "ad1 = " << contbits->debugDrive1.a << std::endl;
            // contbits[0].command
            // auto ccb = &EthercatAPIData::Instance()->ClearBit();
            // ccb->debugDrive1.status = 1;
            for (auto slave : _vectorSlaves) {
                std::cout << "slaveID = " << slave->id << std::endl;
                std::cout << "command = " << contbits[slave->id].command << std::endl;
                std::cout << "status = " << slave->getStatus() << std::endl;
                slave->setCommand(contbits[slave->id].command);
                slave->ControlDrive();
                contbits[slave->id].status = slave->getStatus();
            }
            // std::cout << "status(EthThread) = " << contbits.debugDrive1.status << std::endl;
            // auto ccb = &EthercatAPIData::Instance()->ClearBit();
            // *ccb->debugDrive1.a = 3;
            auto sendStatus = &EthercatAPIData::Instance()->ClearBit();
            sendStatus->debugDrive1.status = contbits.debugDrive1.status;
            sendStatus->debugDrive2.status = contbits.debugDrive2.status;
            EthercatAPIData::Instance()->UpdateControlBits();
            //считывание параметров для драйверов

            //передача параметров в конечные автоматы драйверов

            //запуск конечных автоматов

            cycleState = 1;
            break;
        }
    }

};

class ThreadManager {

    shared_ptr<MainOperator> ecatProcess;
    std::thread ecatThread;
public:
    ThreadManager(){
        ecatProcess = shared_ptr<MainOperator>(new MainOperator);
    }
public:
    void Start() {

        ecatThread = std::thread(&ThreadManager::StartThreadHandler, this);
        ecatThread.detach();
    }

    void *StartThreadHandler() {
        while(1) {
            ecatProcess->Cycle();
        }
        
    }
};

class SlaveApi {
public:
    shared_ptr<ThreadManager> ecatThread;

    SlaveApi() {
        ecatThread = shared_ptr<ThreadManager> (new ThreadManager);
    }

    void StartEthercatThread() {
        ecatThread->Start();
    }

    DevicesStruct& ControlBitRW() 
    {
        DevicesStruct* localcontrolbits;
        // EthercatAPIData::Instance()->ContbitsMutex().lock();
        localcontrolbits = &EthercatAPIData::Instance()->Bits();
        // EthercatAPIData::Instance()->ContbitsMutex().unlock();
        return *localcontrolbits;
    }

    int SendControlBits()
    {
        EthercatAPIData::Instance()->EnableReceivingControlBits();
        return 0;
    }

    int ReadStatus(int slaveIndex) {
        return ControlBitRW()[slaveIndex].status;
    }

    void SendCommand(int _command, int slaveIndex) {
       ControlBitRW()[slaveIndex].command = _command;
       SendControlBits();
    }

    int EnableDrive(int slaveIndex) {
        if (ReadStatus(slaveIndex) == 1) {
            std::cout << "Drive enabled" << std::endl;
            return 1;
        } else {
            SendCommand(1, slaveIndex);
            while(ReadStatus(slaveIndex) != 1) {
                // std::cout << "...." << std::endl;
            }
            std::cout << "END OF ENABLE" << std::endl;
            return 0;
        }
    }

};

int Slave::idStatic = 0;

int main() {

    SlaveApi ethercatApi;
    ethercatApi.StartEthercatThread();
    ethercatApi.ControlBitRW().debugDrive1.a = 10;
    ethercatApi.ControlBitRW().debugDrive1.command = 0;
    ethercatApi.SendControlBits();
    std::this_thread::sleep_for(5000ms);
    // ethercatApi.ControlBitRW()[1].command = 1;
    ethercatApi.EnableDrive(1);
    // ethercatApi.SendControlBits();
    // std::this_thread::sleep_for(5000ms);
    std::cout << "status(mainThread) = " << ethercatApi.ReadStatus(1) << std::endl;
    while (1)
    {
        // std::cout << "END OF ENABLE" << std::endl;
    }
    
}







