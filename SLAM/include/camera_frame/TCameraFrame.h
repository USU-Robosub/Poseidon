//
// Created by Kyler Jensen on 2/15/17.
//

#ifndef SLAM_TCAMERAFRAME_H
#define SLAM_TCAMERAFRAME_H

#include "types.h"
#include "ColorSpace.h"
#include "ICameraFrame.h"
#include <vector>
#include <opencv2/opencv.hpp>

namespace slam {

    template<typename T>
    class TCameraFrame {

    protected:
        virtual void setPixel(int row, int col, const T& value) = 0;

        virtual T getPixel(int row, int col) const = 0;

        void loadFromVector(const std::vector<std::vector<T>> &data) {
            for(uint row = 0; row < data.size(); row++) {
                for(uint col = 0; col < data[row].size(); col++) {
                    setPixel(row, col, data[row][col]);
                }
            }
        }

    };

    template<typename T>
    int get_rows(const std::vector<std::vector<T>> &data) {
        return (int) data.size();
    }

    template<typename T>
    int get_cols(const std::vector<std::vector<T>> &data) {
        size_t max = 0;
        for(auto row : data) {
            max = row.size() > max ? row.size() : max;
        }
        return (int) max;
    }

}



#endif //SLAM_TCAMERAFRAME_H
