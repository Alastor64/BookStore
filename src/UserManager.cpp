#include "UserManager.hpp"
namespace UserManager
{
    int userAdd(const std::vector<std::string> &S)
    {
        if (S.size() != 4)
            return 0;
        User u;
        if (u.ID.check(S.at(0)))
        {
            u.ID = S.at(0);
            std::vector<int> tmp;
            mapID.show(u.ID, tmp);
            if (!tmp.empty())
                return 1;
        }
        else
            return 1;
        if (u.password.check(S.at(1)))
            u.password = S.at(1);
        else
            return 1;
        if (isPRIVILEGE(S.at(2)))
            u.privilege = static_cast<PRIVILEGE>(S.at(2).at(0) - '0');
        else
            return 1;
        if (u.name.check(S.at(3)))
            u.name = S.at(3);
        else
            return 1;
        int index = Data()->Write(&u);
        mapID.insert(std::make_pair(u.ID, index));
        return 0;
    }
}