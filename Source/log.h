#pragma once
#include <fstream>
#include <iostream>
#include <DirectXMath.h>

void LogToFile(const std::string& message) {
    std::ofstream logFile("debug.log", std::ios::app);
    logFile << message << std::endl;
}

void LogMatrix(const DirectX::XMMATRIX& matrix) {
    DirectX::XMFLOAT4X4 mat;
    DirectX::XMStoreFloat4x4(&mat, matrix);
    std::ofstream logFile("debug.log", std::ios::app);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            logFile << mat.m[i][j] << " ";
        }
        logFile << std::endl;
    }
}