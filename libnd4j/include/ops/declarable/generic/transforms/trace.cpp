//
// @author Yurii Shyrma (iuriish@yahoo.com), created on 24.01.2018
//

#include <op_boilerplate.h>
#if NOT_EXCLUDED(OP_trace)

#include <ops/declarable/CustomOperations.h>
#include<ops/declarable/helpers/transforms.h>

namespace nd4j {
namespace ops  {

CUSTOM_OP_IMPL(trace, 1, 1, false, 0, 0) {
    
    NDArray<T>* input  = INPUT_VARIABLE(0);
    NDArray<T>* output = OUTPUT_VARIABLE(0);    
    
    REQUIRE_TRUE(input->rankOf() >= 2, 0, "TRACE op: the rank of input array must be >=2, but got %i instead!", input->rankOf());

    helpers::trace(*input, *output);

    return Status::OK();
}


DECLARE_SHAPE_FN(trace) {
    auto inShapeInfo = inputShape->at(0);

    REQUIRE_TRUE(inShapeInfo[0] >= 2, 0, "TRACE op: the rank of input array must be >=2, but got %i instead!", inShapeInfo[0]);    
    const int rank = inShapeInfo[0] - 2;

    Nd4jLong* outShapeInfo(nullptr);
    ALLOCATE(outShapeInfo, block.getWorkspace(), shape::shapeInfoLength(rank), Nd4jLong); 

    outShapeInfo[0] = rank;
    for(int i=1; i <= rank; ++i)
        outShapeInfo[i] = inShapeInfo[i];

    shape::updateStrides(outShapeInfo, shape::order(inShapeInfo));

    return SHAPELIST(outShapeInfo);
}


}
}

#endif