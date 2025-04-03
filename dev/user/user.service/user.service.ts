import { userInfo } from "../user.dto/user.dto";
import { addnewUserModel, getUserInfoModel } from "../user.model/user.model";

export const addnewUserService = async(
    userInfo : userInfo
):Promise<number> => {
    // 비밀번호 hash하기
    const password = userInfo.password;
    userInfo.password = password;

    const result = await addnewUserModel(userInfo);

    return result;
};

export const getUserInfoService = async(
    userId : number
):Promise<userInfo> => {
    const result = await getUserInfoModel(userId);

    return result;
};