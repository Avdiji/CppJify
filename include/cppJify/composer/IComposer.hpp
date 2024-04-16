#pragma once

#include <sstream>

namespace cppJify::composer {

    class IComposer {
        public:
            virtual const std::ostringstream getOss() const;
    };

}  // namespace cppJify::composer