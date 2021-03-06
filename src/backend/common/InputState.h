// Copyright 2017 The NXT Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef BACKEND_COMMON_INPUTSTATE_H_
#define BACKEND_COMMON_INPUTSTATE_H_

#include "Forward.h"
#include "Builder.h"
#include "RefCounted.h"

#include "nxt/nxtcpp.h"

#include <array>
#include <bitset>

namespace backend {

    size_t IndexFormatSize(nxt::IndexFormat format);
    uint32_t VertexFormatNumComponents(nxt::VertexFormat format);
    size_t VertexFormatSize(nxt::VertexFormat format);

    class InputStateBase : public RefCounted {
        public:
            InputStateBase(InputStateBuilder* builder);

            struct AttributeInfo {
                uint32_t bindingSlot;
                nxt::VertexFormat format;
                uint32_t offset;
            };

            struct InputInfo {
                uint32_t stride;
                nxt::InputStepMode stepMode;
            };

            const std::bitset<kMaxVertexAttributes>& GetAttributesSetMask() const;
            const AttributeInfo& GetAttribute(uint32_t location) const;
            const std::bitset<kMaxVertexInputs>& GetInputsSetMask() const;
            const InputInfo& GetInput(uint32_t slot) const;

        private:
            std::bitset<kMaxVertexAttributes> attributesSetMask;
            std::array<AttributeInfo, kMaxVertexAttributes> attributeInfos;
            std::bitset<kMaxVertexInputs> inputsSetMask;
            std::array<InputInfo, kMaxVertexInputs> inputInfos;
    };

    class InputStateBuilder : public Builder<InputStateBase> {
        public:
            InputStateBuilder(DeviceBase* device);

            // NXT API
            void SetAttribute(uint32_t shaderLocation, uint32_t bindingSlot,
                    nxt::VertexFormat format, uint32_t offset);
            void SetInput(uint32_t bindingSlot, uint32_t stride,
                    nxt::InputStepMode stepMode);

        private:
            friend class InputStateBase;

            InputStateBase* GetResultImpl() override;

            std::bitset<kMaxVertexAttributes> attributesSetMask;
            std::array<InputStateBase::AttributeInfo, kMaxVertexAttributes> attributeInfos;
            std::bitset<kMaxVertexInputs> inputsSetMask;
            std::array<InputStateBase::InputInfo, kMaxVertexInputs> inputInfos;
    };

}

#endif // BACKEND_COMMON_INPUTSTATE_H_
