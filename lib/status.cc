#include "lib/status.h"

namespace error {

std::string_view ToString(const Code code) {
  switch (code) {
    case Code::OK:
      return "OK";
    case Code::CANCELLED:
      return "CANCELLED";
    case Code::UNKNOWN:
      return "UNKNOWN";
    case Code::INVALID_ARGUMENT:
      return "INVALID_ARGUMENT";
    case Code::DEADLINE_EXCEEDED:
      return "DEADLINE_EXCEEDED";
    case Code::NOT_FOUND:
      return "NOT_FOUND";
    case Code::ALREADY_EXISTS:
      return "ALREADY_EXISTS";
    case Code::PERMISSION_DENIED:
      return "PERMISSION_DENIED";
    case Code::RESOURCE_EXHAUSTED:
      return "RESOURCE_EXHAUSTED";
    case Code::FAILED_PRECONDITION:
      return "FAILED_PRECONDITION";
    case Code::ABORTED:
      return "ABORTED";
    case Code::OUT_OF_RANGE:
      return "OUT_OF_RANGE";
    case Code::UNIMPLEMENTED:
      return "UNIMPLEMENTED";
    case Code::INTERNAL:
      return "INTERNAL";
    case Code::UNAVAILABLE:
      return "UNAVAILABLE";
    case Code::DATA_LOSS:
      return "DATA_LOSS";
  }
  return "INVALID";
}

}  // namespace error