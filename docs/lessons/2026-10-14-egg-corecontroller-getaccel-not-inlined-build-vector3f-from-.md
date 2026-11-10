# EGG::CoreController::getAccel() not inlined: build Vector3f from getCoreStatus()

- status: works
- tags: egg,controller,inline
- source: RPBsb_80259bbc

symptom: bl getAccel__Q23EGG14CoreControllerCFv instead of inline copy
cause: out-of-line in this header
fix: EGG::Vector3f acc(st->acc.x, st->acc.y, st->acc.z) from ctrl->getCoreStatus()
