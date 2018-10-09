//
// Copyright © 2017 Arm Ltd. All rights reserved.
// SPDX-License-Identifier: MIT
//

#include <armnn/layers/ConvertFp16ToFp32Layer.hpp>
#include <armnn/layers/ConvertFp32ToFp16Layer.hpp>
#include <armnn/test/TensorHelpers.hpp>

#include <backends/CpuTensorHandle.hpp>
#include <backends/cl/ClWorkloadFactory.hpp>
#include <backends/cl/test/ClContextControlFixture.hpp>
#include <backends/test/IsLayerSupportedTestImpl.hpp>
#include <backends/test/LayerTests.hpp>

#include <boost/test/unit_test.hpp>

#include <string>

BOOST_AUTO_TEST_SUITE(ClLayerSupport)

BOOST_FIXTURE_TEST_CASE(IsLayerSupportedFloat16Cl, ClContextControlFixture)
{
    armnn::ClWorkloadFactory factory;
    IsLayerSupportedTests<armnn::ClWorkloadFactory, armnn::DataType::Float16>(&factory);
}

BOOST_FIXTURE_TEST_CASE(IsLayerSupportedFloat32Cl, ClContextControlFixture)
{
    armnn::ClWorkloadFactory factory;
    IsLayerSupportedTests<armnn::ClWorkloadFactory, armnn::DataType::Float32>(&factory);
}

BOOST_FIXTURE_TEST_CASE(IsLayerSupportedUint8Cl, ClContextControlFixture)
{
    armnn::ClWorkloadFactory factory;
    IsLayerSupportedTests<armnn::ClWorkloadFactory, armnn::DataType::QuantisedAsymm8>(&factory);
}

BOOST_FIXTURE_TEST_CASE(IsConvertFp16ToFp32SupportedCl, ClContextControlFixture)
{
    std::string reasonIfUnsupported;

    bool result = IsConvertLayerSupportedTests<armnn::ClWorkloadFactory, armnn::ConvertFp16ToFp32Layer,
      armnn::DataType::Float16, armnn::DataType::Float32>(reasonIfUnsupported);

    BOOST_CHECK(result);
}

BOOST_FIXTURE_TEST_CASE(IsConvertFp16ToFp32SupportedFp32InputCl, ClContextControlFixture)
{
    std::string reasonIfUnsupported;

    bool result = IsConvertLayerSupportedTests<armnn::ClWorkloadFactory, armnn::ConvertFp16ToFp32Layer,
      armnn::DataType::Float32, armnn::DataType::Float32>(reasonIfUnsupported);

    BOOST_CHECK(!result);
    BOOST_CHECK_EQUAL(reasonIfUnsupported, "Input should be Float16");
}

BOOST_FIXTURE_TEST_CASE(IsConvertFp16ToFp32SupportedFp16OutputCl, ClContextControlFixture)
{
    std::string reasonIfUnsupported;

    bool result = IsConvertLayerSupportedTests<armnn::ClWorkloadFactory, armnn::ConvertFp16ToFp32Layer,
      armnn::DataType::Float16, armnn::DataType::Float16>(reasonIfUnsupported);

    BOOST_CHECK(!result);
    BOOST_CHECK_EQUAL(reasonIfUnsupported, "Output should be Float32");
}

BOOST_FIXTURE_TEST_CASE(IsConvertFp32ToFp16SupportedCl, ClContextControlFixture)
{
    std::string reasonIfUnsupported;

    bool result = IsConvertLayerSupportedTests<armnn::ClWorkloadFactory, armnn::ConvertFp32ToFp16Layer,
      armnn::DataType::Float32, armnn::DataType::Float16>(reasonIfUnsupported);

    BOOST_CHECK(result);
}

BOOST_FIXTURE_TEST_CASE(IsConvertFp32ToFp16SupportedFp16InputCl, ClContextControlFixture)
{
    std::string reasonIfUnsupported;

    bool result = IsConvertLayerSupportedTests<armnn::ClWorkloadFactory, armnn::ConvertFp32ToFp16Layer,
      armnn::DataType::Float16, armnn::DataType::Float16>(reasonIfUnsupported);

    BOOST_CHECK(!result);
    BOOST_CHECK_EQUAL(reasonIfUnsupported, "Input should be Float32");
}

BOOST_FIXTURE_TEST_CASE(IsConvertFp32ToFp16SupportedFp32OutputCl, ClContextControlFixture)
{
    std::string reasonIfUnsupported;

    bool result = IsConvertLayerSupportedTests<armnn::ClWorkloadFactory, armnn::ConvertFp32ToFp16Layer,
      armnn::DataType::Float32, armnn::DataType::Float32>(reasonIfUnsupported);

    BOOST_CHECK(!result);
    BOOST_CHECK_EQUAL(reasonIfUnsupported, "Output should be Float16");
}

BOOST_AUTO_TEST_SUITE_END()