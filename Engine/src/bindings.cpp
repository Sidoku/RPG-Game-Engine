//
// Created by Sanjana Nalawade on 4/11/23.
//

#include <pybind11/pybind11.h>
#include <pybind11/embed.h>
#include "../include/GameWorld/GameModel.h"
#include "Engine.hpp"
namespace py = pybind11;

PYBIND11_MODULE(mygameengine, m){
    py::class_<Engine>(m, "Engine")
            .def(py::init<GameModel*>(), py::arg("GameModel"))
            .def("InitializeGraphicsSubSystem", &Engine::InitializeGraphicsSubSystem)
            .def("Start", &Engine::Start)
            .def("MainGameLoop", &Engine::MainGameLoop)
            .def("Shutdown", &Engine::Shutdown)
            .def("Input", &Engine::Input)
            .def("Update", &Engine::Update)
            .def("Render", &Engine::Render);


    py::class_<GameModel>(m, "GameModel")
            .def(py::init<int,int,int,bool,int,int,std::string,int>(), py::arg("xcoordinate"), py::arg("ycoordinate"),
                 py::arg("interconnectivity"), py::arg("isWrapping"), py::arg("treasurePercentage"),
                 py::arg("monsterCount"), py::arg("playerName"), py::arg("pix"));


}