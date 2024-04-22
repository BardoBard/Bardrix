//
// Created by Bard on 13/03/2024.
//

#include <bardrix/dimension3.h>

std::ostream& bardrix::operator<<(std::ostream& os, const bardrix::dimension3& dimension3) {
    return dimension3.print(os);
}
