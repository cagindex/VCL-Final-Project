#pragma once

#include <vector>

#include "Engine/app.h"

#include "Labs/FinalProject/CaseTest.h"
#include "Labs/Common/UI.h"

namespace VCX::Labs::FinalProject {
    class App : public Engine::IApp {
    private:
        Common::UI      _ui;

        std::size_t     _caseId = 0;

        CaseTest        _caseTest;

        std::vector<std::reference_wrapper<Common::ICase>> _cases = {
            _caseTest,
        };
    public:
        App();

        void OnFrame() override;
    };
}


