import { Request,Response,NextFunction } from "express"
import { userInfo } from "../user.dto/user.dto";
import { addnewUsererrorMessages, addnewUsersuccessMessages, deleteUserErrorMessage, deleteUserSuccessMessage, getUserInfoerrorMessage, getUserInfoSuccessMessage } from "../../errorHandler/userErrorHandler";
import { addnewUserService, deleteUserService, getUserInfoService } from "../user.service/user.service";

export const addnewUserContorller = async (
    req : Request,
    res : Response,
    next : NextFunction
):Promise<void> => {
    try {
        const userInfo = req.body as userInfo;

        if(!userInfo.nickname) {
            res.status(404).json({ errorMessage: addnewUsererrorMessages.missingNickname });
            return;
        }

        if(!userInfo.password) {
            res.status(404).json({ errorMessage: addnewUsererrorMessages.missingPassword });
            return;
        }
        
        const userId = await addnewUserService(userInfo);

        res.status(200).json({ successMessage : addnewUsersuccessMessages(userId) });
        return;
    }catch(error) {
        res.status(500).json({ errorMessage : addnewUsererrorMessages.serverError });
        return;
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
            return;
        }

        const result = await getUserInfoService(userId);

        if(!result) {
            res.status(400).json({ errorMessage : getUserInfoerrorMessage.notFoundUser });
            return;
        }

        res.status(200).json({ successMessage : getUserInfoSuccessMessage(result) });
        return;
    }catch(error) {
        res.status(500).json({ errorMessage : getUserInfoerrorMessage.serverError });
        return;
    }
};

export const deleteUserController = async (
    req : Request,
    res : Response,
    next : NextFunction
): Promise<void> => {
    const userId = Number(req.query.userId);

    try {
        if(!userId) {
            res.status(400).json({ errorMessage : deleteUserErrorMessage.missingUserId });
            return;
        }

        const result = await deleteUserService(userId);

        res.status(202).json({ successMessage : deleteUserSuccessMessage(userId) });
        return;
    } catch (error : any) { 
        res.status(500).json({ errorMesaage : deleteUserErrorMessage.serverError });
        return;
    }
};