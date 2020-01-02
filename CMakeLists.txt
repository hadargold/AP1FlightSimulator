cmake_minimum_required(VERSION 3.15)
project(FlightSimulator)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)
add_executable(FlightSimulator main.cpp Lexer.cpp Lexer.h SymbolTable.cpp SymbolTable.h ex1.cpp ex1.h Expression.h CommandsManager.cpp CommandsManager.h Command.h ConnectCommand.cpp ConnectCommand.h OpenServerCommand.cpp OpenServerCommand.h Parser.cpp Parser.h PrintCommand.cpp PrintCommand.h SleepCommand.cpp SleepCommand.h TCPThread.cpp TCPThread.h UpdateValCommand.cpp UpdateValCommand.h VarCommand.cpp VarCommand.h VariableManager.cpp VariableManager.h Interpreter.cpp Interpreter.h IfCommand.cpp IfCommand.h Condition.cpp Condition.h)