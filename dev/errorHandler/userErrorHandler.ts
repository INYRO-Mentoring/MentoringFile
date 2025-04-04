import { userInfo } from "../user/user.dto/user.dto";

export interface successMessage {
    statusCode : number;
    user_id? : number;
    userInfo? : userInfo;
    message : String;
};

export interface errorMessage {
    statusCode : number;
    message : String;
};


// addnewUser Function
// 에러 메시지 모음
export const addnewUsererrorMessages: Record<string, errorMessage> = {
    missingNickname: { statusCode: 400, message: "닉네임이 누락되었습니다." },
    missingPassword: { statusCode: 400, message: "비밀번호가 누락되었습니다." },
    serverError: { statusCode: 500, message: "서버 에러입니다." },
};

// 성공 메시지 모음
export const addnewUsersuccessMessages = (userId : number):successMessage => ({
    statusCode: 201, user_id : userId, message: "사용자가 등록되었습니다." 
});


// getUserInfo Function
export const getUserInfoerrorMessage:Record<string, errorMessage> = {
    missingUserId: { statusCode : 400, message : "유저 ID가 누락되었습니다."},
    notFoundUser: { statusCode : 400, message : "해당 유저가 없습니다."},
    serverError: { statusCode: 500, message: "서버 에러입니다." }
};


export const getUserInfoSuccessMessage = (userInfo : userInfo):successMessage => ({
    statusCode : 201, userInfo : userInfo, message : "유저 정보를 불러왔습니다."
}); 

// deleteUser function

export const deleteUserErrorMessage: Record<string, errorMessage> = {
    missingUserId: { statusCode : 400, message : "유저 ID가 누락되었습니다."},
    notFoundUser: { statusCode : 400, message : "해당 유저가 없습니다."},
    serverError: { statusCode: 500, message: "서버 에러입니다." }
};

export const deleteUserSuccessMessage = (userId : number):successMessage => ({
    statusCode : 202, user_id : userId, message : "유저를 정삭적으로 삭제하였습니다."
});