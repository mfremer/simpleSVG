#include "SVGMarker.hpp"

#include <sstream>

namespace simpleSVG {

std::string SVGMarker::to_string() const {
    std::stringstream ss;
    ss << "<marker "
       << "id=\"" << m_id << "\" "
       << "style=\"overflow:visible\" "
       << "orient=\"auto-start-reverse\""
       << ">\n";
    ss << m_path.to_string() << '\n';
    ss << "</marker>";
    return ss.str();
}
    
}