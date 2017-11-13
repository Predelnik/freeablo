#include "dialogmanager.h"
#include <cassert>
#include "guimanager.h"

namespace FAGui
{
    DialogLineData& DialogLineData::setAction(std::function<void()> actionArg)
    {
        action = actionArg;
        return *this;
    }

    DialogLineData& DialogData::text_lines(const std::vector<std::string>& texts, TextColor color, bool alignCenter)
    {
        auto& ret = mLines[mLastLine];
        for(auto& text : texts)
        {
            mLines[mLastLine].text = text;
            mLines[mLastLine].color = color;
            mLines[mLastLine].isSeparator = false;
            mLines[mLastLine].alignCenter = alignCenter;
            ++mLastLine;
        }
        skip_line();
        return ret;
    }

    void DialogData::skip_line(int cnt)
    {
        mLastLine += cnt;
    }

    void DialogData::separator()
    {
        mLines[mLastLine].isSeparator = true;
        ++mLastLine;
        skip_line();
    }

    void DialogData::header(const std::vector<std::string>& text)
    {
        if(text.size() == 1)
        {
            skip_line();
            text_lines({text.front()}, TextColor::golden);
            skip_line();
        }
        else
        {
            for(auto& line : text)
            {
                text_lines({line}, TextColor::golden);
            }
        }
        separator();
        skip_line();
    }

    int DialogData::selectedLine()
    {
        if(mSelectedLine == -1)
        {
            auto it = std::find_if(mLines.begin(), mLines.end(),
                                   [](const DialogLineData& data) { return !!data.action; });
            if(it != mLines.end())
                return mSelectedLine = it - mLines.begin();
            assert(false);
        }
        return mSelectedLine;
    }

    DialogManager::DialogManager(GuiManager& gui_manager): mGuiManager(gui_manager)
    {
    }

    void DialogManager::talkOgden()
    {
        DialogData d;
        d.header({"Welcome to the", "Rising Sun"});
        d.skip_line(2);
        d.text_lines({"Would You Like to:"}, TextColor::golden);
        d.skip_line();
        d.text_lines({"Talk to Ogden"}, TextColor::blue).setAction([]()
        {
        });
        d.skip_line(4);
        d.text_lines({"Leave the Tavern"}).setAction([&]()
        {
            mGuiManager.popDialogData();
        });
        mGuiManager.pushDialogData(std::move(d));
    }

    void DialogManager::talkFarnham()
    {
        DialogData d;
        d.header({"Farnham the Drunk"});
        d.skip_line(2);
        d.text_lines({"Would You Like to:"}, TextColor::golden);
        d.skip_line();
        d.text_lines({"Talk to Farnham"}, TextColor::blue).setAction([]()
        {
        });
        d.skip_line(4);
        d.text_lines({"Say Goodbye"}).setAction([&]()
        {
            mGuiManager.popDialogData();
        });
        mGuiManager.pushDialogData(std::move(d));
    }

    void DialogManager::talkAdria()
    {
        DialogData d;
        d.header({"Witch's Shack"});

        d.skip_line(2);
        d.text_lines({"Would You Like to:"}, TextColor::golden);
        d.skip_line();
        d.text_lines({"Talk to Adria"}, TextColor::blue).setAction([]()
        {
        });
        d.text_lines({"Buy Items"}).setAction([]()
        {
        });
        d.text_lines({"Sell Items"}).setAction([]()
        {
        });
        d.text_lines({"Recharge Staves"}).setAction([]()
        {
        });
        d.text_lines({"Leave the Shack"}).setAction([&]()
        {
            mGuiManager.popDialogData();
        });
        mGuiManager.pushDialogData(std::move(d));
    }

    void DialogManager::talkWirt()
    {
        DialogData d;
        d.header({"Wirt the Peg-Legged Boy"});

        d.skip_line();
        d.text_lines({"Talk to Wirt"}, TextColor::blue).setAction([](){
        });
        d.skip_line(2);
        d.text_lines({"I have something for sale,"}, TextColor::golden);
        d.text_lines({"But it will cost 50 gold"}, TextColor::golden);
        d.text_lines({"Just to take a look."}, TextColor::golden);
        d.text_lines({"What have you got?"}).setAction([&]()
        {
        });
        d.text_lines({"Goodbye"}).setAction([&]()
        {
            mGuiManager.popDialogData();
        });
        mGuiManager.pushDialogData(std::move(d));
    }

    void DialogManager::talkPepin()
    {
        DialogData d;
        d.header({"Welcome to the", "Healer's Home"});

        d.skip_line(2);
        d.text_lines({"Would You Like to:"}, TextColor::golden);
        d.skip_line();
        d.text_lines({"Talk to Pepin"}, TextColor::blue).setAction([]()
        {
        });
        d.text_lines({"Receive Healing"}).setAction([]()
        {
        });
        d.text_lines({"Buy Items"}).setAction([]()
        {
        });
        d.text_lines({"Leave Healer's Home"}).setAction([&]()
        {
            mGuiManager.popDialogData();
        });
        mGuiManager.pushDialogData(std::move(d));
    }

    void DialogManager::talkCain()
    {
        DialogData d;
        d.header({"The Town Elder"});
        d.skip_line(2);
        d.text_lines({"Would You Like to:"}, TextColor::golden);
        d.skip_line();
        d.text_lines({"Talk to Cain"}, TextColor::blue).setAction([]()
        {
        });
        d.text_lines({"Identify an Item"}).setAction([]()
        {
        });
        d.skip_line(2);
        d.text_lines({"Say Goodbye"}).setAction([&]()
        {
            mGuiManager.popDialogData();
        });
        mGuiManager.pushDialogData(std::move(d));
    }

    void DialogManager::talkGillian()
    {
        DialogData d;
        d.header({"Gillian"});
        d.skip_line(2);
        d.text_lines({"Would You Like to:"}, TextColor::golden);
        d.skip_line();
        d.text_lines({"Talk to Gillian"}, TextColor::blue).setAction([]()
        {
        });
        d.skip_line(4);
        d.text_lines({"Say Goodbye"}).setAction([&]()
        {
            mGuiManager.popDialogData();
        });
        mGuiManager.pushDialogData(std::move(d));
    }

    void DialogManager::talk(const std::string& npcId)
    {
        if(npcId == "NPCsmith")
            talkGriswold();
        else if(npcId == "NPCtavern")
            talkOgden();
        else if(npcId == "NPCdrunk")
            talkFarnham();
        else if(npcId == "NPCmaid")
            talkGillian();
        else if(npcId == "NPCboy")
            talkWirt();
        else if(npcId == "NPChealer")
            talkPepin();
        else if(npcId == "NPCwitch")
            talkAdria();
        else if(npcId == "NPCstorytell")
            talkCain();
    }

    void DialogManager::talkGriswold()
    {
        DialogData d;
        d.header({"Welcome to the", "Blacksmith's Shop"});
        d.text_lines({"Would You Like to:"}, TextColor::golden);
        d.skip_line();
        d.text_lines({"Talk to Griswold"}, TextColor::blue).setAction([]()
        {
        });
        d.text_lines({"Buy Basic Items"}).setAction([]()
        {
        });
        d.text_lines({"Buy Premium Items"}).setAction([]()
        {
        });
        d.text_lines({"Sell Items"}).setAction([]()
        {
        });
        d.text_lines({"Repair Items"}).setAction([]()
        {
        });
        d.text_lines({"Leave the Shop"}).setAction([&]()
        {
            mGuiManager.popDialogData();
        });
        mGuiManager.pushDialogData(std::move(d));
    }
}
