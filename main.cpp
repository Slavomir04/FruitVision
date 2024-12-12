#include <iostream>
#include <fstream>
#include "src/App/App.h"
#include <vector>
#include "src/Components/SButton/SButton.h"
#include "src/Components/TextField/TextField.h"
#include "src/Components/SImage/SImage.h"
#include <filesystem>
#include <Python.h>
using namespace std;


#include <Python.h>

#include <Python.h>
#include <stdio.h>

void call_python_function(const char *module_name, const char *function_name, const char *image_path, const char *model_path) {
    // Inicjalizacja interpretera Pythona
    Py_Initialize();

    // Import modułu Pythona
    PyObject *pModule = PyImport_ImportModule(module_name);
    if (!pModule) {
        PyErr_Print();
        fprintf(stderr, "Failed to load module '%s'\n", module_name);
        Py_Finalize();
        return;
    }

    // Pobranie funkcji z modułu
    PyObject *pFunc = PyObject_GetAttrString(pModule, function_name);
    if (!pFunc || !PyCallable_Check(pFunc)) {
        PyErr_Print();
        fprintf(stderr, "Cannot find function '%s'\n", function_name);
        Py_DECREF(pModule);
        Py_Finalize();
        return;
    }

    // Przygotowanie argumentów do funkcji
    PyObject *pArgs = PyTuple_Pack(2, PyUnicode_FromString(image_path), PyUnicode_FromString(model_path));
    if (!pArgs) {
        PyErr_Print();
        fprintf(stderr, "Failed to create arguments\n");
        Py_DECREF(pFunc);
        Py_DECREF(pModule);
        Py_Finalize();
        return;
    }

    // Wywołanie funkcji
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    if (pValue) {
        if (PyList_Check(pValue)) {
            printf("Predictions:\n");
            for (Py_ssize_t i = 0; i < PyList_Size(pValue); i++) {
                PyObject *pItem = PyList_GetItem(pValue, i);
                if (PyTuple_Check(pItem) && PyTuple_Size(pItem) == 2) {
                    PyObject *label = PyTuple_GetItem(pItem, 0);
                    PyObject *probability = PyTuple_GetItem(pItem, 1);
                    printf("%s: %.2f\n", PyUnicode_AsUTF8(label), PyFloat_AsDouble(probability));
                }
            }
        }
        Py_DECREF(pValue);
    } else {
        PyErr_Print();
        fprintf(stderr, "Call to function '%s' failed\n", function_name);
    }

    // Sprzątanie
    Py_DECREF(pArgs);
    Py_DECREF(pFunc);
    Py_DECREF(pModule);

    // Finalizacja interpretera Pythona
    Py_Finalize();
}




int main()
{

    float alpha = 0.76f;
   App app(sf::VideoMode::getDesktopMode().width * alpha,sf::VideoMode::getDesktopMode().height * alpha,"App");
   app.vStart();
    /*
    std::string model_path = "C:/programowanie/FruitVision/src/Resources/fruit_classifier_model.h5";
    std::string image_path = "C:/programowanie/FruitVision/src/Resources/mango.png";
    call_python_function("fruitRecognizer3", "getResult", image_path.c_str(), model_path.c_str());
    */
    return 0;
}
