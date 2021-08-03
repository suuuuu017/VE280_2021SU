#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include "Dlist.h"
#include "Instr.h"

const std::string WHITESPACE = " \n\r\t\f\v";
std::string rightTrim(const std::string & line)
{
    size_t end = line.find_last_not_of(WHITESPACE);
    if(end == std::string::npos){
        return "";
    }
    else{
        return line.substr(0, end + 1);
    }
}

void addInstr(Dlist<int> &stack){
    int * ele1 = stack.removeFront();
    int * ele2 = stack.removeFront();
    int result = *ele1 + *ele2;
    int * ele3 = new int(result);
    stack.insertFront(ele3);
    delete ele1;
    delete ele2;
}

void norInstr(Dlist<int> &stack){
    int * ele1 = stack.removeFront();
    int * ele2 = stack.removeFront();
    int result = ~ (*ele1 | *ele2);
    int * ele3 = new int(result);
    stack.insertFront(ele3);
    delete ele1;
    delete ele2;
}

void ifzInstr(Instr& it, Dlist<int> &stack, Dlist<std::string> &queue){
    int * stackNum = stack.removeFront();
    if(*stackNum == 0){
        int removeNum = it.parameter;
        for(int i = 0; i < removeNum; i++){
            delete queue.removeFront();
        }
    }
    delete stackNum;
}

void loadInstr(Dlist<int> &stack, int memoryArray[]){
    int * memoryAdd = stack.removeFront();
//    std::cout << "memory address is " << * memoryAdd << std::endl;
    int memoryCon = memoryArray[*memoryAdd];
    int * tmp = new int(memoryCon);
    stack.insertFront(tmp);
    delete memoryAdd;
}

void storeInstr(Dlist<int> &stack, int memoryArray[]){
    int * address = stack.removeFront();
    int * value = stack.removeFront();
    memoryArray[*address] = *value;
    delete address;
    delete value;
}

void popInstr(Dlist<int> &stack){
    delete stack.removeFront();
}

void pushiInstr(Instr& it, Dlist<int> &stack){
    int * push = new int(it.parameter);
    stack.insertFront(push);
}

void printMemory(int memoryArray[], int memoryLength){
//    std::cout << "memory is ";
    for(int i = 0; i < memoryLength; i++){
        std::cout << memoryArray[i] << " ";
    }
    std::cout << std::endl;
}

void printStack(Dlist<int> &stack){
//    std::cout << "resulting stack is " << stack << std::endl;
    Dlist<int> tmpStack(stack);
    while(!tmpStack.isEmpty()){
        int * out = tmpStack.removeBack();
        std::cout << *out << " ";
        delete out;
    }
    std::cout << std::endl;
}

void printQueue(Dlist<std::string> &queue){
//    std::cout << "resulting queue is " << queue << std::endl;
    std::cout << queue << std::endl;

}

void print(Instr& it, Dlist<int> &stack, Dlist<std::string> &queue, int memoryArray[], int memoryLength){
    std::cout << it << std::endl;
    printStack(stack);
    printQueue(queue);
    printMemory(memoryArray, memoryLength);
}

int main(int argc, char *argv[])
{
    //TODO:write your code here.
    bool slient = false;
    if(argc == 2){
        std::string option = argv[1];
        if(option == "-s"){
            slient = true;
        }
    }
//    std::cout << "slient is " << slient << std::endl;

    std::string line;

    int stackNum = 0;
    int queueNum = 0;

    while(getline(std::cin, line)) {
//        std::cout << line << std::endl;
        line = rightTrim(line);
        std::istringstream ss(line);
        ss >> stackNum >> queueNum;
        break;
    }
//    std::cout << stackNum << " " << queueNum << std::endl;

    Dlist<int> stack;
    getline(std::cin, line);
//        std::cout << line << std::endl;
    line = rightTrim(line);
    std::istringstream sstack(line);
    while(sstack.peek() != EOF){
        int tmpVal = 0;
        sstack >> tmpVal;
        int *ip = new int(tmpVal);
        stack.insertFront(ip);
    }
//    std::cout << "stack is ";
//    printStack(stack);

//    Dlist<Instr> queue;
    Dlist<std::string> queue;
//
    for(int i = 0; i < queueNum; i++) {
//        std::cout << line << std::endl;
        getline(std::cin, line);
        line = rightTrim(line);
        auto *stp = new std::string(line);
        queue.insertBack(stp);
    }
//    std::string * tmp = queue.removeFront();
//    std::cout << "queue is " << queue << std::endl;
//    delete tmp;


    Dlist<int> memory;
    getline(std::cin, line);
    line = rightTrim(line);
//    std::cout << "line is" << line << std::endl;
    std::istringstream ss(line);
    int memoryLength = 0;
    while(ss.peek() != EOF){
        int tmpVal = 0;
        ss >> tmpVal;
        int *ip = new int(tmpVal);
        memory.insertBack(ip);
        memoryLength = memoryLength + 1;
    }

//    std::cout << "memory Length is " << memory << std::endl;

    int memoryArray[memoryLength];
    for(int i = 0; i < memoryLength; i++){
        int * tmp = memory.removeFront();
        memoryArray[i] = * tmp;
        delete tmp;
    }

    while(!queue.isEmpty()){
        std::string * currentIntrString = queue.removeFront();
        std::istringstream instrS(*currentIntrString);
        Instr currentIntr{};
        instrS >> currentIntr;
        if(currentIntr.name == InstrName::HALT){
            if(!slient){
                print(currentIntr, stack, queue, memoryArray, memoryLength);
            }
            delete currentIntrString;
            break;
        }
        else if(currentIntr.name == InstrName::ADD){
            addInstr(stack);
            if(!slient){
                print(currentIntr, stack, queue, memoryArray, memoryLength);
            }
        }
        else if(currentIntr.name == InstrName::NOR){
            norInstr(stack);
            if(!slient){
                print(currentIntr, stack, queue, memoryArray, memoryLength);
            }
        }
        else if(currentIntr.name == InstrName::IFZ){
            ifzInstr(currentIntr, stack, queue);
            if(!slient){
                print(currentIntr, stack, queue, memoryArray, memoryLength);
            }
        }
        else if(currentIntr.name == InstrName::LOAD){
            loadInstr(stack, memoryArray);
            if(!slient){
                print(currentIntr, stack, queue, memoryArray, memoryLength);
            }
        }
        else if(currentIntr.name == InstrName::STORE){
            storeInstr(stack, memoryArray);
            if(!slient){
                print(currentIntr, stack, queue, memoryArray, memoryLength);
            }
        }
        else if(currentIntr.name == InstrName::POP){
            popInstr(stack);
            if(!slient){
                print(currentIntr, stack, queue, memoryArray, memoryLength);
            }
        }
        else if(currentIntr.name == InstrName::PUSHI){
            pushiInstr(currentIntr, stack);
            if(!slient){
                print(currentIntr, stack, queue, memoryArray, memoryLength);
            }
        }
        else if(currentIntr.name == InstrName::NOOP){
            if(!slient){
                print(currentIntr, stack, queue, memoryArray, memoryLength);
            }
            delete currentIntrString;
            continue;
        }
        delete currentIntrString;
    }
    if(slient){
        printStack(stack);
        printMemory(memoryArray, memoryLength);
    }

    return 0;
}
