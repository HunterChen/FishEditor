#pragma once



enum Z_ORDER_FOR_VIEW
{
	zOrder_BackGround = 0,	//
	zOrder_CommonNode,		//普通节点
	zOrder_SpecialNode,		//特殊节点
	zOrder_CoverLayer,		//覆盖层
	zOrder_PopLayer,		//弹出层
	zOrder_DialogBox,		//对话框
	zOrder_ConfirmBox,		//确认框
	zOrder_BlackBoard,		//蒙版层
	zOrder_Prompt,			//信息提示
};



enum PRIORITY_FOR_TOUCH
{
	touch_Unknown = -128,//

	touch_ButtonOnScrollViewOnPromptLayer,
	touch_ScrollViewOnPromptLayer,
	touch_ButtonUnderScrollViewOnPromptLayer,
	touch_ButtonOnPromptLayer,
	touch_PromptLayer,
	touch_ButtonUnderPromptLayer,
	touch_ButtonOnScrollViewUnderPromptLayer,
	touch_ScrollViewUnderPromptLayer,
	touch_ButtonUnderScrollViewUnderPromptLayer,
	touch_SwallowLayerUnderPromptLayer,

	touch_ButtonOnScrollViewOnBlackBoardLayer,
	touch_ScrollViewOnBlackBoardLayer,
	touch_ButtonUnderScrollViewOnBlackBoardLayer,
	touch_ButtonOnBlackBoardLayer,
	touch_BlackBoardLayer,
	touch_ButtonUnderBlackBoardLayer,
	touch_ButtonOnScrollViewUnderBlackBoardLayer,
	touch_ScrollViewUnderBlackBoardLayer,
	touch_ButtonUnderScrollViewUnderBlackBoardLayer,
	touch_SwallowLayerUnderBlackBoardLayer,

	touch_ButtonOnScrollViewOnConfirmBoxLayer,
	touch_ScrollViewOnConfirmBoxLayer,
	touch_ButtonUnderScrollViewOnConfirmBoxLayer,
	touch_ButtonOnConfirmBoxLayer,
	touch_ConfirmBoxLayer,
	touch_ButtonUnderConfirmBoxLayer,
	touch_ButtonOnScrollViewUnderConfirmBoxLayer,
	touch_ScrollViewUnderConfirmBoxLayer,
	touch_ButtonUnderScrollViewUnderConfirmBoxLayer,
	touch_SwallowLayerUnderConfirmBoxLayer,

	touch_ButtonOnScrollViewOnDialogLayer,
	touch_ScrollViewOnDialogLayer,
	touch_ButtonUnderScrollViewOnDialogLayer,
	touch_ButtonOnDialogLayer,
	touch_DialogLayer,
	touch_ButtonUnderDialogLayer,
	touch_ButtonOnScrollViewUnderDialogLayer,
	touch_ScrollViewUnderDialogLayer,
	touch_ButtonUnderScrollViewUnderDialogLayer,
	touch_SwallowLayerUnderDialogLayer,

	touch_ButtonOnScrollViewOnPopLayer,
	touch_ScrollViewOnPopLayer,
	touch_ButtonUnderScrollViewOnPopLayer,
	touch_ButtonOnPopLayer,
	touch_PopLayer,
	touch_ButtonUnderPopLayer,
	touch_ButtonOnScrollViewUnderPopLayer,
	touch_ScrollViewUnderPopLayer,
	touch_ButtonUnderScrollViewUnderPopLayer,
	touch_SwallowLayerUnderPopLayer,

	touch_ButtonOnScrollViewOnSpecialLayer,
	touch_ScrollViewOnSpecialLayer,
	touch_ButtonUnderScrollViewOnSpecialLayer,
	touch_ButtonOnSpecialLayer,
	touch_SpecialLayer,
	touch_ButtonUnderSpecialLayer,
	touch_ButtonOnScrollViewUnderSpecialLayer,
	touch_ScrollViewUnderSpecialLayer,
	touch_ButtonUnderScrollViewUnderSpecialLayer,
	touch_SwallowLayerUnderSpecialLayer,

	touch_ButtonOnScrollViewOnCoverLayer,
	touch_ScrollViewOnCoverLayer,
	touch_ButtonUnderScrollViewOnCoverLayer,
	touch_ButtonOnCoverLayer,
	touch_CoverLayer,
	touch_ButtonUnderCoverLayer,
	touch_ButtonOnScrollViewUnderCoverLayer,
	touch_ScrollViewUnderCoverLayer,
	touch_ButtonUnderScrollViewUnderCoverLayer,
	touch_SwallowLayerUnderCoverLayer,

	touch_ButtonOnScrollViewOnCommonLayer,
	touch_ScrollViewOnCommonLayer,
	touch_ButtonUnderScrollViewOnCommonLayer,
	touch_ButtonOnCommonLayer,
	touch_CommonLayer,
	touch_ButtonUnderCommonLayer,
	touch_ButtonOnScrollViewUnderCommonLayer,
	touch_ScrollViewUnderCommonLayer,
	touch_ButtonUnderScrollViewUnderCommonLayer,
	touch_SwallowLayerUnderCommonLayer,

	touch_ButtonOnScrollViewOnBackGround,
	touch_ScrollViewOnBackGround,
	touch_ButtonUnderScrollViewOnBackGround,
	touch_ButtonOnBackGround,
	touch_BackGround,
	touch_ButtonUnderBackGround,
	touch_ButtonOnScrollViewUnderBackGround,
	touch_ScrollViewUnderBackGround,
	touch_ButtonUnderScrollViewUnderBackGround,
	touch_SwallowLayerUnderBackGround,
};