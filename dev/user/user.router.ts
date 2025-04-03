import { Router } from 'express';
import { addnewUserContorller, getUserInfoController } from './user.controller/user.controller';

const router = Router();

router.post('/addNewUser', addnewUserContorller);
router.get('/getUserInfo', getUserInfoController);


export default router;