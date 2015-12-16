<?php getView("HeaderView.inc", null); ?>
<div id="feed">
	<form action="?action=changePassword" method="post">
		<p><input type="password" placeholder="Введите старый пароль" name="OldPass"/></p>
		<p><input type="password" placeholder="Введите новый пароль" name="NewPass1"/></p>
		<p><input type="password" placeholder="Повторите новый пароль" name="NewPass2"/></p>
		<p><input type="submit" value="Изменить"></p>
	</form>
</div>
<?php getView("Footer.inc", null); ?>
</body>
