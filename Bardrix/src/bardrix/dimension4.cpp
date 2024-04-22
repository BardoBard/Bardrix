//
// Created by Bard on 13/03/2024.
//

#include <bardrix/dimension4.h>

std::ostream& bardrix::operator<<(std::ostream& os, const bardrix::dimension4& dimension4) {
    return dimension4.print(os);
}
