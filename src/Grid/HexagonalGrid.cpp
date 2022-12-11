#include "HexagonalGrid.h"

namespace Grid {
    int HexagonalGridCubeCoordinates::CalculateS() const {
        return -Q-R;
    }
} // Grid