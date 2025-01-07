//
// Created by slawe on 01.12.2024.
//

#include "ImageRecognizer_1.h"

ImageRecognizer_1::ImageRecognizer_1() {
    Py_Initialize();
    vPreLoad();
}

ImageRecognizer_1::~ImageRecognizer_1() {
    Py_Finalize();
}

std::vector<std::pair<std::string, double>> ImageRecognizer_1::vecGetResult() {
    std::vector<std::pair<std::string, double>> result;
    if (isLoadedImage && isLoadedModel) {
        PyObject* pResult = callPythonFunction("getResult", str_path_image, str_path_model);
        if (pResult && PyList_Check(pResult)) {
            Py_ssize_t size = PyList_Size(pResult);
            for (Py_ssize_t i = 0; i < size; ++i) {
                PyObject* pItem = PyList_GetItem(pResult, i);
                if (pItem && PyTuple_Check(pItem)) {
                    PyObject* pLabel = PyTuple_GetItem(pItem, 0);
                    PyObject* pProb = PyTuple_GetItem(pItem, 1);

                    std::string label = PyUnicode_AsUTF8(pLabel);
                    double probability = PyFloat_AsDouble(pProb);
                    result.emplace_back(label, probability);

                }
            }
        }
        Py_XDECREF(pResult);
    } else {
        if (!isLoadedImage) {
            result.emplace_back("", static_cast<double>(ImageRecognizer::ProblemType::NO_IMAGE));
        }
        if (!isLoadedModel) {
            result.emplace_back("", static_cast<double>(ImageRecognizer::ProblemType::NO_MODEL));
        }
    }
    return result;
}

bool ImageRecognizer_1::vLoadModel(std::string str_adres) {
    PyObject* pResult = callPythonFunction("isPathModelCorrect", str_adres);
    if (pResult && PyObject_IsTrue(pResult)) {
        str_path_model = str_adres;
        isLoadedModel = true;
        Py_DECREF(pResult);
        return true;
    }
    Py_XDECREF(pResult);
    return false;
}

bool ImageRecognizer_1::vLoadImage(std::string str_adres) {
    PyObject* pResult = callPythonFunction("isPathImageCorrect", str_adres);
    if (pResult && PyObject_IsTrue(pResult)) {
        str_path_image = str_adres;
        isLoadedImage = true;
        Py_DECREF(pResult);
        return true;
    }
    Py_XDECREF(pResult);
    return false;
}

bool ImageRecognizer_1::vLoadModel(std::wstring str_adres) {
    throw std::runtime_error("wstring is not implemented yet");
}

bool ImageRecognizer_1::vLoadImage(std::wstring str_adres) {
    throw std::runtime_error("wstring is not implemented yet");
}

void ImageRecognizer_1::vPreLoad() {
    vLoadImage("");
    vLoadModel("");
}

PyObject* ImageRecognizer_1::callPythonFunction(const std::string& funcName, const std::string& arg1, const std::string& arg2) {
    return callPythonFunctionInternal(funcName, {arg1, arg2});
}

PyObject* ImageRecognizer_1::callPythonFunction(const std::string& funcName, const std::string& arg1) {
    return callPythonFunctionInternal(funcName, {arg1});
}

PyObject* ImageRecognizer_1::callPythonFunctionInternal(const std::string& funcName, const std::vector<std::string>& args) {

    const std::string pythonScriptPath = std::string(IMAGE_RECOGNIZER_PATH)+std::string(IMAGE_RECOGNIZER_SCRIPT_NAME)+".py";
    PyObject* pName = nullptr;
    PyObject* pModule = nullptr;
    PyObject* pFunc = nullptr;
    PyObject* pArgs = nullptr;
    PyObject* pValue = nullptr;

    try {


        pName = PyUnicode_DecodeFSDefault(IMAGE_RECOGNIZER_SCRIPT_NAME);
        //PyRun_SimpleString(("import sys; sys.path.append('" + std::filesystem::current_path().string() + "/Resources')").c_str());
        PyRun_SimpleString(("import sys; sys.path.append('" + std::string(IMAGE_RECOGNIZER_PATH) + "')").c_str());
       // PyRun_SimpleString("import sys; sys.path.append('../Resources')");
        if (!pName) {
            throw std::runtime_error("Failed to decode script path.");
        }


        pModule = PyImport_Import(pName);
        Py_DECREF(pName);

        if (!pModule) {
            throw std::runtime_error("Failed to load Python script.");
        }


        pFunc = PyObject_GetAttrString(pModule, funcName.c_str());
        if (!pFunc || !PyCallable_Check(pFunc)) {
            throw std::runtime_error("Failed to retrieve function: " + funcName);
        }


        pArgs = PyTuple_New(args.size());
        if (!pArgs) {
            throw std::runtime_error("Failed to create argument tuple.");
        }

        for (size_t i = 0; i < args.size(); ++i) {
            PyObject* pArg = PyUnicode_FromString(args[i].c_str());
            if (!pArg) {
                throw std::runtime_error("Failed to convert argument to Python string.");
            }
            PyTuple_SetItem(pArgs, i, pArg);
        }


        pValue = PyObject_CallObject(pFunc, pArgs);
        if (!pValue) {
            throw std::runtime_error("Failed to call Python function.");
        }


        // Cleanup
        Py_DECREF(pFunc);
        Py_DECREF(pModule);
        Py_DECREF(pArgs);
    } catch (const std::exception& e) {
        // Cleanup
        Py_XDECREF(pFunc);
        Py_XDECREF(pModule);
        Py_XDECREF(pArgs);
        Py_XDECREF(pValue);
        throw std::runtime_error(std::string(e.what()));
    }


    return pValue;
}

std::string ImageRecognizer_1::strGetModelPath() {
    return str_path_model;
}

std::string ImageRecognizer_1::strGetImagePath() {
    return str_path_image;
}
