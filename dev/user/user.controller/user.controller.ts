import { Request,Response,NextFunction } from "express"
import { userInfo } from "../user.dto/user.dto";
import { addnewUsererrorMessages, addnewUsersuccessMessages, getUserInfoerrorMessage, getUserInfoSuccessMessage } from "../../errorHandler/userErrorHandler";
import { addnewUserService, getUserInfoService } from "../user.service/user.service";

export const addnewUserContorller = async (
    req : Request,
    res : Response,
    next : NextFunction
):Promise<void> => {
    try {
        const userInfo = req.body as userInfo;

        if(!userInfo.nickname) {
            res.status(404).json({ errorMessage: addnewUsererrorMessages.missingNickname });
        }

        if(!userInfo.password) {
            res.status(404).json({ errorMessage: addnewUsererrorMessages.missingPassword });
        }
        
        const userId = await addnewUserService(userInfo);

        res.status(200).json({ successMessage : addnewUsersuccessMessages(userId) });

    }catch(error) {
        res.status(500).json({ errorMessage : addnewUsererrorMessages.serverError });
    };
};

export const getUserInfoController = async (
    req : Request,
    res : Response,
    next : NextFunction
):Promise<void> => {
    
    const userId = Number(req.query.userId);

    try {
        if(!userId) {
            res.status(400).json({ errorMessage : getUserInfoerrorMessage.missingUserId });
        }

        const result = await getUserInfoService(userId);

        if(!result) {
            res.status(400).json({ errorMessage : getUserInfoerrorMessage.notFoundUser });
        }

        res.status(200).json({ successMessage : getUserInfoSuccessMessage(result) });

    }catch(error) {
        res.status(500).json({ errorMessage : getUserInfoerrorMessage.serverError });
    }
};